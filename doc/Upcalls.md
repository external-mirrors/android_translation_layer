#### How to do C->Java JNI calls

note: skip to Rationale if you want full context, then come back

##### On the Java side

Add an `@Export` annotation to any method you want to call from C. If the method you
want to call is not part of api-impl, instead add the method signature to `extern_upcalls.txt`.

If multiple methods with the same name (using overloading, which is not supported in C) need
to be exported, you must use `@Export(<disambiguated-name>)`, where `disambiguated-name` is what
you would call the method if Java didn't support overloading either, assuming you were to call it
something of the form `<existing-name>_<suffix>`. `<existing-name>` in case of a constructor should
be `constructor`, which is what plain `@Export` with no parameters would result in. For consistency,
if more than one overloaded method is exported, all of them must specify a name, but the "default"
one (if there is such a notion) can use `@Export(<existing-name>)`.

If you need to get the `jclass` for a class which doesn't contain any exported methods,
add an `@Export` annotation to the class itself.

`extern_upcalls.txt` entry format: `com/example/Class.method(II)V:exportedName`
(leave out `:exportedName` if not renaming an overloaded function, and leave out
`.method(II)V` as well to only export the class itself.)

##### On the C side

No new `Call<Type>Method` invocations should be added.

To call a Java method, first "export" it (see above). After it's exported, run `ninja` to generate
the wrapper. This step is optional, if you're not using code completion you probably don't care
if it gets generated now or later.

An exported method can be called using the generated wrapper. The wrapper function's name
is `J__<unqualified-class-name>__<method-name>`, and the first argument is `env`, followed by `this`
(the `jobject` you want the method to operate on), unless the method is a static method in which
case `env` is immediately followed by the method's actual arguments (if any). Unlike with
`CallObjectMethod`, the return type will be `jstring`, `jclass` or `jthrowable` if appropriate.

Use `_CACHED_CLASS(UnqualifiedName)` if you need to obtain the `jclass`.

##### Caveats / TODOs

No new `FindClass` invocations should be added, and some existing ones should be removed,
however we don't currently support annotating classes to indicate that cached proxy getters
for a jclass should be generated even though no method of that class is exported.

We use the `--short-classes` option of the generator tool, which means collisions are possible.
Detecting a collision currently causes the generation to be aborted. If we at some point need
to export methods of multiple classes that all share the same name, we will need to figure out
a way to handle that which doesn't require using the fully qualified class names.

#### Rationale

##### Preface

To call a Java function from C using JNI, you generally use code like this:
```
jclass class = (*env)->FindClass(env, "com/example/Class");
jmethodID method = (*env)->GetMethodID(env, class, "exampleMethod", "(II)V");
env->CallVoidMethod(env, object, method, 42, 69);
```

Since the lookup is not free, it's common to cache the classes and methods. From a UX perspective,
this means the actual call site will only contain the last function. That is, unless you decide
that it may be a good idea to initialize the cache lazily.

The `Call<Type>Method` function is a variadic function. This means that despite both Java and C
having strong typing, and the types of the arguments being, in principle, knowable at compile time,
there is no type checking happening here. Are the arguments the right type? Is there the right
number of arguments? Does that class even exist? These are all things that are knowable at compile
time, but they are not in any way verified.

To fix this, and perhaps improve the UX, some projects (seem to?) use approaches like C++ classes
which mirror the Java class hierarchy. These are *presumably* automatically generated using type
information from the Java files (or resulting class files), thus providing type checking. Lazy
initialization of the cache is also easy to add into the generated wrappers.

##### Options

In C, we obviously can't use C++ classes. We could, with some massaging, use a `const struct`,
resulting in usage like `J.com.example.ClassName(env, object, 42, 69)`. Note that we still
have to pass `env` (well, we don't *have* to, but it's presumably more performant than calling
`JavaVM.getEnv`), and of course we have to pass the object, since there's no implicit `this`
in C (and even in C++ it would incur unnecessary runtime overhead to use a wrapper class).
We could however do `J.com.example.StaticClassName(env, 42, 69)` since we have the `jclass`
in the cache anyway (`CallStatic<Type>Method` takes a `jclass` instead of a `jobject`).

Now, speaking of unnecessary runtime overhead: In principle, it should be possible for the
wrapper to be a zero-cost abstraction. Just an `always_inline` function that calls the variadic
function, resulting in identical code generation but with type checking at compile-time.
We did decide to add calls to getters for lazy initialization of the cache, but those would
be present in any case as long as we want the cache to be initalized lazily.  
We can however *not* use the dot notation if we want to guarantee zero cost abstraction - while
`constexpr struct` is a thing in C, it is annoyingly not allowed to fill it with function pointers,
and even then it's unclear whether `always_inline` functions invoked through what are technically
pointers are still guaranteed to get inlined.

We may still change to the dot notation in the future, since while it's not guaranteed, there
are ways to strongly encourage the compiler to independently decide that it would be a good
idea to optimize out the indirection. (a `static const struct` defined in the header, so that
it's effectively defined in every compilation unit - no LTO needed for the compiler to figure
out that it's just an unnecessary wrapper)

##### Current Design

see top of the doc
