package csv;

import java.util.*;
import java.util.List;
import java.util.function.Predicate;

class TableImpl implements Table {

    private List<Column> columnList;
    private List<Integer> key;

    TableImpl(String[] h) {
        columnList = new ArrayList<>();
        for (int i=0; i<h.length; i++){
            Column c;
            c = new ColumnImpl(h[i]);
            columnList.add(c);
        }
        key = new ArrayList<Integer>();
    }

    TableImpl(int f){
        columnList = new ArrayList<>();
        for (int i=0; i<f; i++){
            Column c;
            c = new ColumnImpl();
            columnList.add(c);
        }
        key = new ArrayList<Integer>();
    }

    public TableImpl(Table t){
        columnList = new ArrayList<>();
        for (int i=0; i<t.getColumnCount(); i++) {
            Column c = new ColumnImpl(t.getColumn(i).getHeader());
            columnList.add(c);
        }
        key = new ArrayList<Integer>();
    }

    private void madeKey(int byIndexOfColumn, boolean isAscending, boolean isNullFirst){
        ColumnImpl column = (ColumnImpl) columnList.get(byIndexOfColumn);

        if (column.getNumericCount()==0) {
            for (int i = 0; i < column.count(); i++) {
                String s = column.getValue(i);
                Integer K = 0;
                for (int j = 0; j < column.count(); j++) {
                    String v = column.getValue(j);

                    if (isAscending && isNullFirst) {  // t t
                        if (s.compareTo(v) > 0) {
                            K++;
                        } else if (s.compareTo(v) == 0) {
                            if (j < i) {
                                K++;
                            }
                        }
                    } else if (!(isAscending || isNullFirst)) {  // f f
                        if (s.compareTo(v) < 0) {
                            K++;
                        } else if (s.compareTo(v) == 0) {
                            if (j > i) {
                                K++;
                            }
                        }
                    } else if (isAscending && !isNullFirst) { //t f
                        if (!v.equals("") && s.compareTo(v) > 0) {
                            K++;
                        }
                        if (s.compareTo(v) == 0) {
                            if (j < i) {
                                K++;
                            }
                        } else if (s.equals("")) {
                            K++;
                        }
                    } else if (!isAscending && isNullFirst) {  // f t
                        if (!v.equals("") && (s.compareTo(v) < 0)) {
                            K++;
                        }
                        if (s.compareTo(v) == 0) {
                            if (j > i) {
                                K++;
                            }
                        }
                    }
                }
                key.add(i, K);
            }
        }

        else {
            for (int i=0; i<column.count(); i++){ key.add(i); }
            if (isAscending) { //!
                for (int i = 0; i < column.count(); i++) {
                    try {
                        Double.valueOf(column.getValue(i));
                    } catch (NumberFormatException e) {
                        continue;
                    }
                    Double s = Double.valueOf(column.getValue(i));
                    Integer K = 0;
                    for (int j = 0; j < column.count(); j++) {
                        try {
                            Double.valueOf(column.getValue(j));
                        } catch (NumberFormatException e) {
                            continue;
                        }

                        Double v = Double.valueOf(column.getValue(j));

                        if (isNullFirst) {  // t t
                            if (s.compareTo(v) > 0) {
                                K++;
                            } else if (s.compareTo(v) == 0) {
                                if (j < i) {
                                    K++;
                                }
                            }
                        }  else { //t f
                            if (s.compareTo(v) > 0) {
                                K++;
                            }
                            if (s.compareTo(v) == 0) {
                                if (j < i) {
                                    K++;
                                }
                            }
                        }
                    }
                    key.set(i, K);
                }

                for (int i = 0; i < column.count(); i++) {
                    try {
                        Double.valueOf(column.getValue(i));
//                    System.out.println("try 1");
                    } catch (NumberFormatException e) {

                        String s = column.getValue(i);
                        Integer K = (int) column.getNumericCount();
                        for (int j = 0; j < column.count(); j++) {
                            try {
                                Double.valueOf(column.getValue(j));
//                            System.out.println("try 2");
                            } catch (NumberFormatException ee) {
                                String v = column.getValue(j);

                                if (isNullFirst) {
                                    if (s.compareTo(v) > 0) {
                                        K++;
                                    } else if (s.compareTo(v) == 0) {
                                        if (j < i) {
                                            K++;
                                        }
                                    }
                                }  else {
                                    if (!v.equals("") && (s.compareTo(v) < 0)) {
                                        K++;
                                    }
                                    if (s.compareTo(v) == 0) {
                                        if (j > i) {
                                            K++;
                                        }
                                    }
                                }
//                            System.out.println(K + "@@@@@@@@@@");
                            }
                        }
                        key.set(i, K);
                    }
                }
            }

            else { //내림차순
//                System.out.println("^^^^^^^^^^^^");
                for (int i = 0; i < column.count(); i++) {
                    try {
                        Double.valueOf(column.getValue(i));
//                    System.out.println("try 1");
                    } catch (NumberFormatException e) {
                        String s = column.getValue(i);
                        Integer K = 0;
                        for (int j = 0; j < column.count(); j++) {
                            try {
                                Double.valueOf(column.getValue(j));
//                            System.out.println("try 2");
                            } catch (NumberFormatException ee) {
                                String v = column.getValue(j);

                                 if (!isNullFirst) {
                                    if (s.compareTo(v) < 0) {
                                        K++;
                                    } else if (s.compareTo(v) == 0) {
                                        if (j > i) {
                                            K++;
                                        }
                                    }
                                } else {
                                    if (!v.equals("") && s.compareTo(v) > 0) {
                                        K++;
                                    }
                                    if (s.compareTo(v) == 0) {
                                        if (j < i) {
                                            K++;
                                        }
                                    } else if (s.equals("")) {
                                        K++;
                                    }
                                }
//                            System.out.println(K + "@@@@@@@@@@");
                            }
                        }
                        key.set(i, K);
                    }
                }

                for (int i = 0; i < column.count(); i++) { // 내림차순
                    try {
                        Double.valueOf(column.getValue(i));
                    } catch (NumberFormatException e) {
                        continue;
                    }
                    Double s = Double.valueOf(column.getValue(i));
                    Integer K = (int) column.getNumericCount();
                    for (int j = 0; j < column.count(); j++) {
                        try {
                            Double.valueOf(column.getValue(j));
                        } catch (NumberFormatException e) {
                            continue;
                        }

                        Double v = Double.valueOf(column.getValue(j));

                        if (isNullFirst) {
                            if (s.compareTo(v) < 0) {
                                K++;
                            } else if (s.compareTo(v) == 0) {
                                if (j > i) {
                                    K++;
                                }
                            }
                        } else {
                            if (s.compareTo(v) > 0) {
                                K++;
                            }
                            if (s.compareTo(v) == 0) {
                                if (j < i) {
                                    K++;
                                }
                            }
                        }
                    }
                    key.set(i, K);
                }
            }
        }

//        System.out.println(key);
    }

    @Override
    public void print() {
        Column c = getColumn(1);
        if (!(c.getHeader() == "")) {
            for (Column column : columnList) {
                ColumnImpl column1 = (ColumnImpl) column;
                int longest = column1.getLongest();
                String s = column.getHeader();
                if (s == null){ s = "null"; }
                System.out.printf(" %" + longest + "s |", s);
            }
            System.out.println("");
        }
            for (int i = 0; i < c.count(); i++) {
//                System.out.print(i+" @@@@");
                for (Column column : columnList) {
                    ColumnImpl column1 = (ColumnImpl) column;
                    int longest = column1.getLongest();
                    String s = column.getValue(i);
                    if (s.isEmpty()) {
                        s = "null";
                    }
                    System.out.printf(" %" + longest + "s |", s);
                }
                System.out.println("");

        }
    }

    public Table getStats() {
        String[] header = new String[columnList.size()+1];

        header[0] = " ";

        List<Integer> index = new ArrayList<>();
        index.add(-1);
        int j, length = 1;
        for (int i=0; i<columnList.size(); i++) {
            if (!(columnList.get(i).getNumericCount() == 0)) {
                header[length++] = columnList.get(i).getHeader();
                index.add(i);
            }

        }

        String[] newHeder = new String[length];

        for (int i=0; i<length; i++)
            newHeder[i]=header[i];

        Table table = new TableImpl(newHeder);

        String[] first = {"count", "mean", "std", "min", "25%", "50%", "75%", "max"};

        for (int i=0; i<first.length; i++){
            for (j=1; j<index.size(); j++){
                table.getColumn(0).setValue(i, first[i]);
                Column tableColumn = table.getColumn(j);
                Column column = getColumn(index.get(j));
                switch (i) {
                    case 0 :
                        tableColumn.setValue(i, column.getNumericCount());
                        break;

                    case 1 :
                        tableColumn.setValue(i, String.format("%.6f", column.getMean()));
                        break;

                    case 2 :
                        tableColumn.setValue(i, String.format("%.6f", column.getStd()));
                        break;

                    case 3 :
                        tableColumn.setValue(i, column.getNumericMin());
                        break;

                    case 4 :
                        tableColumn.setValue(i, column.getQ1());
                        break;

                    case 5 :
                        tableColumn.setValue(i, column.getMedian());
                        break;

                    case 6 :
                        tableColumn.setValue(i, column.getQ3());
                        break;

                    case 7 :
                        tableColumn.setValue(i, column.getNumericMax());
                        break;
                }
            }
        }

//        System.out.println(newHeder);

        return table;
    }

    public Table head() {
        Table table = head(5);
        return table;
    }

    public Table head(int lineCount) {
        Table table = new TableImpl(this);

        for (int i = 0; i < lineCount; i++) {
            for (int j=0; j<table.getColumnCount(); j++) {
                table.getColumn(j).setValue(i, getColumn(j).getValue(i));
            }
        }

        return table;
    }

    public Table tail() {
        Table table = tail(5);
        return table;
    }

    public Table tail(int lineCount) {
        Table table = new TableImpl(this);

        for (int i = 0; i < lineCount; i++) {
            for (int j=0; j<table.getColumnCount(); j++) {
                Column c = getColumn(j);
                table.getColumn(j).setValue(i, c.getValue(c.count()-lineCount+i));
            }
        }

        return table;
    }

    public Table selectRows(int beginIndex, int endIndex) {
        Table table = new TableImpl(this);
        int lineCount = endIndex - beginIndex;

        for (int i = 0; i < (lineCount); i++) {
            for (int j=0; j<table.getColumnCount(); j++) {
                Column c = getColumn(j);
                table.getColumn(j).setValue(i, c.getValue(beginIndex+i));
            }
        }

        return table;
    }

    public Table selectRowsAt(int... indices) {
        Table table = new TableImpl(this);

        for (int i=0; i<indices.length; i++) {
            for (int j=0; j<table.getColumnCount(); j++) {
                Column c = getColumn(j);
                table.getColumn(j).setValue(i, c.getValue(indices[i]));
            }
        }

        return table;
    }

    public Table selectColumns(int beginIndex, int endIndex) {
        int Count = endIndex - beginIndex;
        String[] header = new String[Count];

        int j=0;
        for (int i= beginIndex; i<endIndex; i++){
            header[j++] = columnList.get(i).getHeader();
        }

        Table table = new TableImpl(header);

        for (int i = 0; i < columnList.get(0).count(); i++) {
            for (j=0; j<Count; j++) {
                table.getColumn(j).setValue(i, getColumn(j).getValue(i));
            }
        }
        return table;
    }

    public Table selectColumnsAt(int... indices) {
        String[] header = new String[indices.length];

        for (int i=0; i<indices.length; i++){
            header[i] = columnList.get(i).getHeader();
        }
        Table table = new TableImpl(header);

        for (int i = 0; i < columnList.get(0).count(); i++) {
            for (int j=0; j<indices.length; j++) {
                table.getColumn(j).setValue(i, getColumn(j).getValue(i));
            }
        }
        return table;
    }

    public <T> Table selectRowsBy(String columnName, Predicate<T> predicate) {
        return null;
    }

    public Table sort(int byIndexOfColumn, boolean isAscending, boolean isNullFirst) {
        madeKey(byIndexOfColumn, isAscending, isNullFirst);

        for (Column c : columnList) {
            ColumnImpl column = (ColumnImpl) c;
            List<String> newList = new ArrayList<>();

            for (int i=0; i<c.count(); i++){
                newList.add("");
            }

            for (int i=0; i<c.count(); i++) {
                newList.set(key.get(i), c.getValue(i));
            }
            column.setList(newList);
        }

        return this;
    }

    public Table shuffle() {
        for (int i=0; i<columnList.get(0).count(); i++){ key.add(i); }

        Collections.shuffle(key);

        System.out.println(key);

        for (Column c : columnList) {
            ColumnImpl column = (ColumnImpl) c;
            List<String> newList = new ArrayList<>();

            for (int i=0; i<c.count(); i++){
                newList.add("");
            }

            for (int i=0; i<c.count(); i++) {
                newList.set(key.get(i), c.getValue(i));
            }
            column.setList(newList);
        }

        return this;
    }

    public int getRowCount() {
        return columnList.get(0).count();
    }

    public int getColumnCount() {
        return columnList.size();
    }

    public Column getColumn(int index) {
        final Column column = columnList.get(index);
        return column;
    }

    public Column getColumn(String name) {
        for (Column c : columnList){
            if (name == c.getHeader()){
                return c;
            }
        }
        return null;
    }

    public boolean fillNullWithMean() {
        boolean cnt = false;

        for (Column c : columnList) {
            if (c.isNumericColumn()) {
                ColumnImpl column = (ColumnImpl) c;
                List<String> newList = new ArrayList<>();
                double mean = c.getMean();

                for (int i = 0; i < c.count(); i++) {
                    if (c.getValue(i).equals("")){
                        newList.add(String.format("%.6f", mean));
                        cnt = true;
                    }else {
                        newList.add(c.getValue(i));
                    }
                }

                column.setList(newList);
            }
        }

        return cnt;
    }

    public boolean fillNullWithZero() {
        boolean cnt = false;

        for (Column c : columnList) {
            if (c.isNumericColumn()) {
                ColumnImpl column = (ColumnImpl) c;
                List<String> newList = new ArrayList<>();

                for (int i = 0; i < c.count(); i++) {
                    if (c.getValue(i).equals("")){
                        newList.add("0");
                        cnt = true;
                    }else {
                        newList.add(c.getValue(i));
                    }
                }

                column.setList(newList);
            }
        }

        return cnt;
    }

    public boolean standardize() {
        return false;
    }

    public boolean normalize() {
        return false;
    }

    public boolean factorize() {
        return false;
    }

    @Override
    public String toString() {
        int size, columnSize, nullSize, typeSize;
        String data = "";

        for (int i = 0; i < columnList.size(); i++) {
            for (Column column : columnList) {
                ColumnImpl column1 = (ColumnImpl) column;
                int longest = column1.getLongest();
                String s = column.getValue(i);
                if (s.isEmpty()) {
                    s = "null";
                }
                String.format(" %" + longest + "s |", s);
            }
//            System.out.println("");
        }

        return "<" + getClass().getName() + "@" + Integer.toHexString(hashCode()) + ">\n" + "RangeIndex: " +
                columnList.get(0).count() +
                " entries, 0 to " + (columnList.get(0).count() - 1) + "\nData columns (total " + columnList.size() +
                " columns):\n" + data;

    }
}
