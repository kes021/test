import java.util.Scanner;

class Door {
    void push() {
        System.out.println("push to open");

    }
    public void open () {
        push();
    }
}

class BankVaultDoor extends Door {

    boolean enter_combination() {
        System.out.println("Enter password:");
        Scanner sc = new Scanner(System.in);
        String input = sc.next();
        if (input.equals("0000")) {
            return true;
        } else
            return false;
    }
    void pull(boolean pin) {
        if (pin)
            System.out.println("pull to open");
        else
            System.out.println("Incorrect password");
    }

    public void open () {
        pull(enter_combination());
    }
}

class HouseFrontDoor extends Door {
    boolean unlock_door() {
        System.out.println("The door is locked. Do you want to open it? (y/n)");
        Scanner sc = new Scanner(System.in);
        String input = sc.next();
        System.out.println(input);
        if (input.equals("y")) {
            return true;
        } else
            return false;
    }

    public void open () {
        if (unlock_door())
            super.open();
        else
            System.out.println("The door is still locked!");
    }
}

class CarDoor extends HouseFrontDoor {

}



public class Inheritance {

    public static void main(String[] args) {
        Door d1 = new BankVaultDoor();
        Door d2 = new HouseFrontDoor();
        Door d3 = new CarDoor();

        try {
            System.out.println(args[0]);
            if ( args[0].equals("car") ) {
                d3.open();
                return;
            }
            if (args[0].equals("bank")) {
                d1.open();
                return;
            }
            d2.open();
        } catch (Exception e) {
            System.err.println(e);
        }
    }
}
