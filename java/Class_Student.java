abstract class Person {
    private String name;
    public int id;

    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }
    public void printName() {
        System.out.println(name);
    }
    abstract public void setID(int id);
    public void printID() {
        System.out.println(id);
    }
}

class Student extends Person {
    public void setID(int id) {
        this.id = id;
    }
}




public class Class_Student {
    public static void main (String[] args) {
        Person s1 = new Student();

        s1.setName("Hasnun");
        s1.printName();
        s1.setID(1);
        s1.printID();
    }
}

