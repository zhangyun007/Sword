class MyClass {
	private double val;
	//����������List<super T>��Set<extends T>����������ʲô��˼�أ�
	//<super T>��ʾ����T���ڵ��κ�T�ĸ��࣬<extends T>��ʾ����T���ڵ��κ�T�����ࡣ
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