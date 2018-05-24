class Door {
    public void open () {
        push();
    }
}

class BackVaultDoor extends Door {
    public void open () {
        enter_combination();
        pull();
    }
}

class HouseFrontDoor extends Door {
    public void open () {
        unlock_door();
        super.open();
    }
}



public class Inheritance {

    public static void main(String[] args) {
        Door d1 = new BankVaultDoor();
        Door d2 = new HouseFrontDoor();
        Door d3 = new CarDoor();

        if ( args[0] == "car" ) {
            d3.open();
        } else if (args[0] == "bank") {
            d1.open();
        } else {
            d2.open();
        }
    }
}
