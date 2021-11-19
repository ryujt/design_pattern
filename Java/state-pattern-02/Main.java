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

class StateNoCoin extends State {
    public void insertCoin() {
        context.setState(new StateHasCoin());
    }

    public void refund() {
        System.out.println("반환 할 동전이 없습니다.");
    }

    public void selectItem() {
        System.out.println("동전을 먼저 넣어 주세요.");
    }

    public void takeItem() {
        System.out.println("꺼낼 상품이 없습니다.");
    }
}

class StateHasCoin extends State {
    public void insertCoin() {
        System.out.println("이미 동전을 투입하셨습니다.");
    }

    public void refund() {
        System.out.println("동전을 반환합니다.");
        context.setState(new StateNoCoin());
    }

    public void selectItem() {
        context.setState(new ItemReleased());
    }

    public void takeItem() {
        System.out.println("꺼낼 상품이 없습니다.");
    }
}

class ItemReleased extends State {
    public void insertCoin() {
        System.out.println("상품을 먼저 꺼내주세요.");
    }

    public void refund() {
        System.out.println("반환 할 동전이 없습니다.");
    }

    public void selectItem() {
        System.out.println("상품을 먼저 꺼내주세요.");
    }

    public void takeItem() {
        context.setState(new StateNoCoin());
    }
}

class Main {
    public static void main(String[] args) {
        VendingMachine machine = new VendingMachine();
        machine.setState(new StateNoCoin());

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
