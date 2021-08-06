package csv;

import java.io.*;

public class CSVs {
    /**
     * @param isFirstLineHeader csv 파일의 첫 라인을 헤더(타이틀)로 처리할까요?
     */

    public static Table createTable(File csv, boolean isFirstLineHeader) throws FileNotFoundException {
        Table t = null;
        BufferedReader br = new BufferedReader(new FileReader(csv));
        String line = "";

        try {
            String [] tokens = null;
            if (isFirstLineHeader){
                line = br.readLine();
                String[] header = line.split(",", -1);
                t = new TableImpl(header);
                line = br.readLine();
            }
            else {
                line = br.readLine();
                String[] firstLine = line.split(",", -1);
                t = new TableImpl(firstLine.length);
//                System.out.println("^^^^^^^^"+line);
            }

            int j = 0;
            do {
//                System.out.println(line);
                tokens = line.split(",", -1);
//                System.out.println("\n" + tokens[] + "\n" + j);

                int cnt=0;
                String temp="";
                String result="";

                for(int i=0;i<tokens.length;i++){
                    if(tokens[i].indexOf("\"")==0){
                        if(tokens[i].lastIndexOf("\"")==tokens[i].length()-1){
                            result+=tokens[i].replaceAll("\"","");
                        }else{
                            cnt++;
                            temp+=tokens[i].replaceAll("\"","");
                        }
                    }else if(tokens[i].lastIndexOf("\"")==tokens[i].length()-1){
                        if(cnt>0){
                            result+=temp+","+tokens[i].replaceAll("\"","");
                            cnt=0;
                            temp="";
                        }
                    }else{
                        if(cnt>0){
                            cnt++;
                            temp+=","+tokens[i].replaceAll("\"","");
                        }else{
                            result+=tokens[i];
                        }
                    }
                    if(i!=tokens.length-1 && cnt==0)result+="|,|";
                }
                tokens=result.split("\\|,\\|");

                int tokenLength = tokens.length;

                if (line.charAt(line.length()-1) == ',' )
                    tokenLength++;

                for (int i=0; i< tokenLength; i++) {
                    
                    Column c = t.getColumn(i);
                    if (tokens.length == i){
                        c.setValue(j, "");
                    }
                    else {
                        if (tokens[i].isEmpty()) { c.setValue(j, ""); }
                        else { c.setValue(j, tokens[i]); }
                    }
//                    System.out.print("*" + tokens[i] + "^ ");

                }
//                System.out.println("|||||END!!");
                j++;
            } while ((line = br.readLine()) != null);

//            for (int i=0; i<10; i++) {
//                ColumnImpl c = (ColumnImpl) t.getColumn(i);
//
//                System.out.println(c.getType() + "///");
//            }

        }
        catch (IOException e) {
            var message = e.getMessage();
        }

     return t;
    }

    /**
     * @return 새로운 Table 객체를 반환한다. 즉, 첫 번째 매개변수 Table은 변경되지 않는다.
     */
    public static Table sort(Table table, int byIndexOfColumn, boolean isAscending, boolean isNullFirst) {
        Table t = new TableImpl(table);

        for (int i = 0; i < table.getColumn(0).count(); i++) {
            for (int j=0; j<table.getColumnCount(); j++) {
                t.getColumn(j).setValue(i, table.getColumn(j).getValue(i));
            }
        }

        t.sort(byIndexOfColumn, isAscending, isNullFirst);

        return t;
    }

    /**ColumnImpl column1 = (ColumnImpl) column;
     int longest = column1.getLongest();
     * @return 새로운 Table 객체를 반환한다. 즉, 첫 번째 매개변수 Table은 변경되지 않는다.
     */
    public static Table shuffle(Table table) {
        Table t = new TableImpl(table);

        for (int i = 0; i < table.getColumn(0).count(); i++) {
            for (int j=0; j<table.getColumnCount(); j++) {
                t.getColumn(j).setValue(i, table.getColumn(j).getValue(i));
            }
        }

        t.shuffle();

        return t;
    }
}
