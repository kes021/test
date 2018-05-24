import java.util.*;

public class TimerScheduleDelay extends TimerTask {
   public static void main(String[] args) {

      // creating timer task, timer
      TimerTask tasknew = new TimerScheduleDelay();
      Timer timer = new Timer();

      // scheduling the task at interval
      timer.schedule(tasknew, 1);
   }
   // this method performs the task

   public void run() {
      System.out.println("timer working");
   }
}
