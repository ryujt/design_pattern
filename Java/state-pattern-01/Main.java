import java.util.Scanner;

class VendingMachine {
    public void setState(State state) {
        this.state = state;
        state.context = this;
        System.out.println("상태변경: " + state.toString());
    }

    public State getState() {
        return state;
    }

    private State state;
}

class State {
    VendingMachine context = null;
    public void insertCoin() {}
    public void refund() {}
    public void selectItem() {}
    public void takeItem() {}
}

class Main {
    public static void main(String[] args) {
        VendingMachine machine = new VendingMachine();

        Scanner in = new Scanner(System.in);
        while (true) {
            String line = in.nextLine();
            switch (line) {
                case "i": machine.getState().insertCoin(); break;
                case "r": machine.getState().refund(); break;
                case "s": machine.getState().selectItem(); break;
                case "t": machine.getState().takeItem(); break;
                case "q": return;
            }
        }
    }
}
