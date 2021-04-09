import java.util.Scanner;

public class opp2_6 {
    public static void main(String[] args){
        System.out.print("1~99 사이의 정수를 입력하시오>>");
        Scanner scanner = new Scanner(System.in);

        int a = scanner.nextInt();
        int b = a / 10;
        int c = a % 10;


        if (c==3||c==6||c==9) {
            System.out.print("박수짝");
            if (b == 3 || b == 6 || b == 9)
                System.out.print("짝");
        }

    }
}
