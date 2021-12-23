import java.util.Scanner;

public class opp3_4 {
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);

        char alp = 'a';
        char alp_array[] = new char[26];

        for (int i=0; i<26; i++){
            alp_array[i] = alp;
            alp++;
        }


        String s = scanner.next();
        char c = s.charAt(0);
        int a;

        for (int i=0; i<26; i++){
            if (c == alp_array[i]){
                a = i;
            }
        }

        for (int i=0; i<a; i++){
            for ();
            System.out.print();

        }

    }

}
