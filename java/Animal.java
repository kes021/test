interface Animal {

    boolean feed(boolean timetoeat);
    void groom();
    void pet();
}

class Dog implements Animal {
    boolean feed(boolean timetoeat) {
        if (timetoeat) {
            System.out.println("Put food into the bowl!");
            return true;
        }
        return false;
    }
    void groom() {
        if (!feed(timetoeat))
            System.out.println("Brush well!");
        else
            System.out.println("Feed first!");
    }
    void pet() {
        if (!feed(timetoeat))
            System.out.println("Pet!");
        else
            System.out.println("Feed first!");
    }
}




public class Animal {
    public static void main (String args[]) {
        Animal dog = new Dog();

    }
}
