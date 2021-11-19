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

class FlyNoWay implements StrategyFly {
    public void fly() {
        System.out.println("No Way! I can't fly.");
    }
}

class FlyWithWings implements StrategyFly {
    public void fly() {
        System.out.println("Yes! I can fly.");
    }
}

class WalkWithTwoFoot implements StrategyWalk {
    public void walk() {
        System.out.println("Walking with two foot...");
    }
}

class WalkWithFourFoot implements StrategyWalk {
    public void walk() {
        System.out.println("Walking with four foot...");
    }
}

class Ostrich extends Animal {
    Ostrich() {
        super(new FlyNoWay(), new WalkWithTwoFoot());
    }
}

class Eagle extends Animal {
    Eagle() {
        super(new FlyWithWings(), new WalkWithTwoFoot());
    }
}

class Lion extends Animal {
    Lion() {
        super(new FlyNoWay(), new WalkWithFourFoot());
    }
}

public class Main {
    public static void main(String[] args) {
        Ostrich ostrich = new Ostrich();
        Eagle eagle = new Eagle();
        Lion lion = new Lion();

        Scanner in = new Scanner(System.in);
        while (true) {
            String line = in.nextLine();
            switch (line) {
                case "f1": ostrich.fly(); break;
                case "w1": ostrich.walk(); break;

                case "f2": eagle.fly(); break;
                case "w2": eagle.walk(); break;

                case "f3": lion.fly(); break;
                case "w3": lion.walk(); break;

                case "q": return;
            }
        }
    }
}
