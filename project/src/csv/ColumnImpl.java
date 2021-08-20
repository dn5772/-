package csv;

import java.util.*;


class ColumnImpl implements Column{

    private String header;
    private int type;                 // 2=String, 1=Double, 0=Int
    private long numericCount;
    private int longest;

    private List<String> valueList;


    private int valueType(String s){
        if (s.isEmpty()){
            return -1;
        }

        try {
            Integer.parseInt(s);
            return 0;
        }
        catch(NumberFormatException e) {
            try {
                Double.parseDouble(s);
                return 1;
            }
            catch (NumberFormatException ee){
                return 2;
            }
        }
    }

    
    private void inPutValue (String value) {
        int valType = valueType(value);

        switch (valType) {
            case 0 :
            case 1 :
                numericCount++;
                break;
        }

        if (valType > type){
            type = valType;
        }

        if (value.length() > longest){
            longest = value.length();
        }

        if (value.isEmpty()){
            if (4 > longest){ longest = 4;}
        }
    }

    
    public ColumnImpl() {
        header = null;
        type = 0;
        numericCount = 0;
        valueList = new ArrayList<String>();
        longest = 0;
    }

    public ColumnImpl(String h){
        header = h;
        type = 0;
        numericCount = 0;
        valueList = new ArrayList<String>();
        longest = h.length();
    }

    void setList(List<String> list) {
        for (String value : list) {
            if (value.length() > longest) {
                longest = value.length();
            }
        }
        valueList = list;
    }

    @Override
    public String getHeader() { return header;}

    public String getValue(int index) {
        String value;
        value = valueList.get(index);
        return value;
    }

    int getLongest(){
        return longest;
    }

    public <T extends Number> T getValue(int index, Class<T> t) throws NumberFormatException{
            String valueSt = valueList.get(index);
            String className = t.getName();

            if (Objects.equals(className, "java.lang.Integer")) {
                return (T) Integer.valueOf(valueSt);
            }

            if (Objects.equals(className, "java.lang.Double")) {
                var valueDouble = (T) Double.valueOf(valueSt);
                return valueDouble;
            }

        return null;
    }


    public void setValue(int index, String value) {
        inPutValue(value);
        valueList.add(index, value);
    }


    public <T extends Number> void setValue(int index, T value) {
        String s = String.valueOf(value);
        inPutValue(s);
        valueList.add(index, s);
    }


    public int count() {
        return valueList.size();
    }

    public void print() {
        for (int i=0; i<valueList.size(); i++){
            System.out.print(valueList.get(i)+"^ ");
        }
        System.out.println("");
    }


    public boolean isNumericColumn() {
        return type != 2;
    }

    int getType() {
        return type;
    }

    public long getNullCount() {
        long nullCount = 0;
        for (String s : valueList){
            if (s.equals("")){ nullCount++; }
        }
        return nullCount;
    }


    public long getNumericCount() {return numericCount;}


    public double getNumericMin() throws NumberFormatException{
        if (numericCount == 0){
            throw new NumberFormatException();
        } else {
            List<Double> doubleList = new ArrayList<>();

            for (int i=0; i<valueList.size(); i++){
                try {
                    doubleList.add(Double.valueOf(valueList.get(i)));
                }
                catch (NumberFormatException e){
                    doubleList.add(999999999.9);
                }
            }

            Collections.sort(doubleList);

            return doubleList.get(0);
        }
    }


    public double getNumericMax() throws NumberFormatException{
        if (numericCount == 0){
            throw new NumberFormatException();
        } else {
            List<Double> doubleList = new ArrayList<>();
            int errcnt = 0;

            for (int i=0; i<valueList.size(); i++){
                try {
                    doubleList.add(Double.valueOf(valueList.get(i)));
                }
                catch (NumberFormatException e){
                    doubleList.add(999999999.9);
                    errcnt++;
                }
            }

            Collections.sort(doubleList);

            return doubleList.get((int)numericCount-1);
        }
    }

    public double getMean() {
        if (numericCount == 0){
            throw new NumberFormatException();
        } else {
            List<Double> doubleList = new ArrayList<>();
            double sum = 0.0;

            for (int i=0; i<valueList.size(); i++){
                try {
                    doubleList.add(Double.valueOf(valueList.get(i)));
                    sum += Double.valueOf(valueList.get(i));
                }
                catch (NumberFormatException e){
                    doubleList.add(999999999.9);
                }
            }

            return sum/numericCount;
        }
    }

    public double getStd() {
        if (numericCount == 0){
            throw new NumberFormatException();
        } else {
            List<Double> doubleList = new ArrayList<>();
            double sum = 0.0, dev, mean;

            for (int i=0; i<valueList.size(); i++){
                try {
                    doubleList.add(Double.valueOf(valueList.get(i)));
                    sum += Double.valueOf(valueList.get(i));
                }
                catch (NumberFormatException e){
                    doubleList.add(999999999.9);
                }
            }

            mean = sum/numericCount;

            sum = 0.0;
            for (Double d : doubleList) {
                if (d == 999999999.9) continue;
                else {
                    dev = (d - mean);
                    sum += Math.pow(dev, 2);
                }
            }

            return Math.sqrt(sum / numericCount);
        }
    }


    public double getQ1() {
        if (numericCount == 0){
            throw new NumberFormatException();
        } else {
            List<Double> doubleList = new ArrayList<>();

            for (int i = 0; i < valueList.size(); i++) {
                try {
                    doubleList.add(Double.valueOf(valueList.get(i)));
                } catch (NumberFormatException e) {
                    doubleList.add(999999999.9);
                }
            }

            Collections.sort(doubleList);
            double q1;

            if (numericCount%2 == 0){
                int medianIndex = (int)numericCount/2;
                if (medianIndex % 2 == 0) {
                    q1 = (doubleList.get(medianIndex/2-1) + doubleList.get(medianIndex/2)) / 2;
                } else {
                    q1 = doubleList.get(medianIndex/2);
                }
            } else {
                int medianIndex = (int)numericCount/2+1;
                if (medianIndex % 2 == 0) {
                    q1 = (doubleList.get(medianIndex/2-1) + doubleList.get(medianIndex/2)) / 2;
                } else {
                    q1 = doubleList.get(medianIndex/2);
                }
            }
            return q1;
        }
    }

    public double getMedian() {
        if (numericCount == 0){
            throw new NumberFormatException();
        } else {
            List<Double> doubleList = new ArrayList<>();

            for (int i = 0; i < valueList.size(); i++) {
                try {
                    doubleList.add(Double.valueOf(valueList.get(i)));
                } catch (NumberFormatException e) {
                    doubleList.add(9999999.9);
                }
            }

            Collections.sort(doubleList);

            if (numericCount%2 == 0){
                int medianIndex = (int)numericCount/2 -1;

                return (doubleList.get(medianIndex) + doubleList.get(medianIndex + 1)) / 2;
                }
            else {
                int medianIndex = (int)numericCount/2;
                return doubleList.get(medianIndex);
            }
        }
    }

    public double getQ3() {
        if (numericCount == 0){
            throw new NumberFormatException();
        } else {
            List<Double> doubleList = new ArrayList<>();

            for (int i = 0; i < valueList.size(); i++) {
                try {
                    doubleList.add(Double.valueOf(valueList.get(i)));
                } catch (NumberFormatException e) {
                    doubleList.add(9999999.9);
                }
            }

            Collections.sort(doubleList);
            double q3;

            if (numericCount%2 == 0){
                int medianIndex = (int)numericCount/2;
                if (medianIndex % 2 == 0) {
                    q3 = (doubleList.get(medianIndex/2*3 -2) + doubleList.get(medianIndex/2*3-1)) / 2;
                } else {
                    q3 = doubleList.get(medianIndex/2*3);
                }
            } else {
                int medianIndex = (int)numericCount/2+1;
                if (medianIndex % 2 == 0) {
                    q3 = (doubleList.get(medianIndex/2*3 -1) + doubleList.get(medianIndex/2*3)) / 2;
                } else {
                    q3 = doubleList.get(medianIndex/2*3-1);
                }
            }


            return q3;
        }
    }

    public boolean fillNullWithMean() {
        return false;
    }

    public boolean fillNullWithZero() {
        return false;
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
}
