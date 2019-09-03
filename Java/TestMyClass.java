class MyClass {
	private double val;
	//经常发现有List<super T>、Set<extends T>的声明，是什么意思呢？
	//<super T>表示包括T在内的任何T的父类，<extends T>表示包括T在内的任何T的子类。
	<T extends Number> MyClass(T arg) {
		val = arg.doubleValue();
	}
	void showval() {
		System.out.println("val: " + val);
	}
}

public class TestMyClass {
	public static void main(String args[]) {
		MyClass test = new MyClass(100);
		MyClass test2 = new MyClass(123.5F);
		test.showval();
		test2.showval();
	}
}