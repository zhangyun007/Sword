import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;
  
class PersonService {
		private String name;
		public void setName(String name) {
			this.name = name;
		}
		public void info() {
			System.out.println("His name is: " + name);
		}
}

public class SpringTest {
	public static void main(String[] args) {
		ApplicationContext ctx = new ClassPathXMLApplicationContext("bean.xml");
		System.out.println(ctx);
		
		PersonService p = ctx.getBean("personService", PersonService.class);
		p.info();
	}
}