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
    public void cancelItem() {}
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

    public  void cancelItem() {
        System.out.println("상품을 먼저 선택해 주세요.");
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
        context.setState(new ItemReleasing());
    }

    public void cancelItem() {
        System.out.println("상품을 먼저 선택해 주세요.");
    }
}

class ItemReleasing extends State {
    public void insertCoin() {
        System.out.println("상품 배출 중입니다.");
    }

    public void refund() {
        System.out.println("상품 배출 중입니다.");
    }

    public void selectItem() {
        System.out.println("상품 배출 중입니다.");
    }

    public void cancelItem() {
        context.setState(new StateHasCoin());
    }
}

class ItemReleased extends State {
    public void insertCoin() {
        System.out.println("상품 배출 완료, 잠시만 기다려주세요.");
    }

    public void refund() {
        System.out.println("상품 배출 완료, 잠시만 기다려주세요.");
    }

    public void selectItem() {
        System.out.println("상품 배출 완료, 잠시만 기다려주세요.");
    }

    public void cancelItem() {
        System.out.println("상품 배출 완료, 잠시만 기다려주세요.");
    }
}

class Main {
    public static void main(String[] args) {
        VendingMachine machine = new VendingMachine();
        machine.setState(new StateNoCoin());
        while (true) {
            Scanner in = new Scanner(System.in);
            String line = in.nextLine();
            switch (line) {
                case "i": machine.getState().insertCoin(); break;
                case "r": machine.getState().refund(); break;
                case "s": machine.getState().selectItem(); break;
                case "c": machine.getState().cancelItem(); break;
                case "q": return;
            }
        }
    }
}
