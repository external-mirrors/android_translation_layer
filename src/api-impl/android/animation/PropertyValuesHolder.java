package android.animation;

import java.lang.reflect.Method;
import android.util.Log;
import android.util.Property;

public class PropertyValuesHolder {

	private float values_float[];
	private int values_int[];
	private Object values_object[];
	private Object value;
	private String property_name;
	private Method setter;

	public static PropertyValuesHolder ofFloat(String propertyName, float... values) {
		PropertyValuesHolder propertyValuesHolder = new PropertyValuesHolder();
		propertyValuesHolder.values_float = values;
		propertyValuesHolder.property_name = propertyName;
		return propertyValuesHolder;
	}

	public static PropertyValuesHolder ofObject(String propertyName, TypeEvaluator evaluator, Object... values) {
		PropertyValuesHolder propertyValuesHolder = new PropertyValuesHolder();
		propertyValuesHolder.values_object = values;
		propertyValuesHolder.property_name = propertyName;
		return propertyValuesHolder;
	}

	public static PropertyValuesHolder ofInt(String propertyName, int... values) {
		PropertyValuesHolder propertyValuesHolder = new PropertyValuesHolder();
		propertyValuesHolder.values_int = values;
		propertyValuesHolder.property_name = propertyName;
		return propertyValuesHolder;
	}

	public static PropertyValuesHolder ofFloat(Property property, float... values) {
		PropertyValuesHolder propertyValuesHolder = new PropertyValuesHolder();
		propertyValuesHolder.values_float = values;
		propertyValuesHolder.property_name = property.getName();
		return propertyValuesHolder;
	}

	public static PropertyValuesHolder ofObject(Property property, TypeEvaluator evaluator, Object... values) {
		PropertyValuesHolder propertyValuesHolder = new PropertyValuesHolder();
		propertyValuesHolder.values_object = values;
		propertyValuesHolder.property_name = property.getName();
		return propertyValuesHolder;
	}

	public static PropertyValuesHolder ofInt(Property property, int... values) {
		PropertyValuesHolder propertyValuesHolder = new PropertyValuesHolder();
		propertyValuesHolder.values_int = values;
		propertyValuesHolder.property_name = property.getName();
		return propertyValuesHolder;
	}

	public void setIntValues(int... values) {
		values_int = values;
	}

	public void setFloatValues(float... values) {
		values_float = values;
	}

	public void setObjectValues(Object... values) {
		values_object = values;
	}

	public String getProperty_name() {
		return property_name;
	}

	public void setProperty_name(String propertyName) {
		this.property_name = propertyName;
	}

	public void setProperty(Property property) {
		property_name = property.getName();
	}

	public void init() {}

	public Object getAnimatedValue() {
		return value;
	}

	public void setEvaluator(TypeEvaluator value) {}

	public void calculateValue(float fraction) {
		if (values_object != null) {
			value = values_object[(int) (fraction * (values_object.length - 1) + 0.5f)];
		} else if (values_float != null) {
			int i = (int) (fraction * (values_float.length - 1));
			float f = fraction * (values_float.length - 1) - i;
			value = values_float[i] * (1 - f) + ((f!=0.f) ? values_float[i + 1] * f : 0.f);
		} else if (values_int != null) {
			int i = (int) (fraction * (values_int.length - 1));
			float f = fraction * (values_int.length - 1) - i;
			value = (int)(values_int[i] * (1 - f) + ((f!=0.f) ? values_int[i + 1] * f : 0.f) + 0.5f);
		} else {
			Log.e("PropertyValuesHolder", "No values set");
		}
	}

	public PropertyValuesHolder clone() {
		return null;
	}

	public void setupSetterAndGetter(Object target) {
		try {
			Class<?> clazz;
			if (values_float != null) {
				clazz = float.class;
			} else {
				clazz = values_object[0].getClass();
			}
			setter = target.getClass().getMethod("set" + property_name.substring(0, 1).toUpperCase() + property_name.substring(1), clazz);
		} catch (NoSuchMethodException e) {
			Log.e("PropertyValuesHolder", "failed to find setter", e);
		}
	}

	public void setupStartValue(Object target) {
	}

	public void setupEndValue(Object target) {
	}

	public void setAnimatedValue(Object target) {
		if (setter != null && value != null) {
			try {
				setter.invoke(target, value);
			} catch (ReflectiveOperationException e) {
				Log.e("PropertyValuesHolder", "failed to invoke setter", e);
			}
		} else {
			Log.e("PropertyValuesHolder", "no setter or value set");
		}
	}
}
