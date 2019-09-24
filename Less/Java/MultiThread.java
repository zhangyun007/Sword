import java.lang.Thread;

class MyThread extends Thread {
    public void run() {
        for (int i = 0; i < 1000; i++) {
            System.out.print(i + " ");
        }
    }
}
public class MultiThread {
    public static void main(String[] args) {
        MyThread t = new MyThread();
        t.start();    
        for (int i = 1001; i < 2000; i++) {
            System.out.print(i + " ");
        }
    }
}