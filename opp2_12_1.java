import java.util.Scanner;

public class opp2_12_1 {
    public static void main(String[] args){
        System.out.print("연산>>");
        Scanner scanner = new Scanner(System.in);

        float a = scanner.nextInt();
        String b = scanner.next();
        float c = scanner.nextInt();

        if (b.equals("/")) {
            if (c == 0)
                System.out.print("0으로 나눌 수 없습니다.");
        }
            else{
                System.out.print(a);
                System.out.print(b);
                System.out.print(c);
                System.out.print ("의 계산 결과는 ");

                if (b.equals("+"))
                    System.out.println(a+c);
                else if (b.equals("-"))
                    System.out.println(a-c);
                else if (b.equals("*"))
                    System.out.println(a*c);
                else if (b.equals("/"))
                    System.out.println(a/c);
        }
    }
}
