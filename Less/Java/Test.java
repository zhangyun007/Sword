import java.util.Collection;
import java.util.Iterator;
import java.util.ArrayList;

public class Test {
	public static void main(String[] args) {
		
		//Pair<int> p = new Pair<>(1, 2); // compile error!

		Collection<String> col=new ArrayList<String>();
		col.add("abc");
		col.add("bcd");
		
		Iterator<String> it=col.iterator();
		
		while(it.hasNext()){
				System.out.println(it.next());
		}    
		
		String str = "Hello";
		System.out.println(str);
	}
}