import java.util.Scanner;

interface StrategyFly {
    public void fly();
}

interface StrategyWalk {
    public void walk();
}

class Animal {
    Animal(StrategyFly strategyFly, StrategyWalk strategyWalk) {
        this.strategyFly = strategyFly;
        this.strategyWalk = strategyWalk;
    }

    public void fly() {
        strategyFly.fly();
    }

    public void walk() {
        strategyWalk.walk();
    }

    private StrategyFly strategyFly;
    private StrategyWalk strategyWalk;
}

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        while (true) {
            String line = in.nextLine();
            switch (line) {
                case "f1": break;
                case "w1": break;

                case "f2": break;
                case "w2": break;

                case "f3": break;
                case "w3": break;

                case "q": return;
            }
        }
    }
}
