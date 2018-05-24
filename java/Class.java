abstract class Point {
    int a;
    int b;

//    Point() {
//    }

    Point(int x, int y) {
        this.a = x;
        this.b = y;
    }


public void print_point() {
    System.out.println(a + ", " + b);
}

public void get_values(int x, int y) {
    this.a = x;
    this.b = y;
}

abstract public void scale_half();

}

class generic_Point extends Point {

public generic_Point(int x, int y) {
    super(x, y);
}

public void scale_half() {
    this.a = this.a / 2;
    this.b = this.b / 2;
}

}


class even_Point extends Point {

public even_Point(int x, int y) {
    super(x, y);
    if (x % 2 != 0 || y % 2 != 0) {
        throw ("this point should be generic");
    }
}

public void scale_half() {
    this.a = this.a / 2;
    this.b = this.b / 2;
}

}






public class Class {

public static void main (String[] args) {
    Point member = new generic_Point(2,3);
    member.print_point();

    Point member2 = new even_Point(16, 2);
    member2.print_point();

    member2.scale_half();
    member2.print_point();

    for (int i = 0; i < args.length; i++) {
        System.out.println(args[i]);
    }
}

}
