package android.atl.annotation;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

/**
 * Used by our tool to generate upcall wrappers with strong typing
 */
@Retention(RetentionPolicy.RUNTIME) // necessary as long as we use asm on the jar rather than a plugin
@Target({ElementType.CONSTRUCTOR, ElementType.METHOD})
public @interface Export {
	/**
	 * alternative exported name (to disambiguate overloaded methods)
	 */
	String value() default "";
}
