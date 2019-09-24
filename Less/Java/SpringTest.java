import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class SpringTest {
	public static void main(String[] args) {
		ApplicationContext ctx = new ClassPathXMLApplicationContext("bean.xml");
		System.out.println(ctx);
		
		PersonService p = ctx.getBean("personService", PersonService.class);
		p.info();
	}
}
