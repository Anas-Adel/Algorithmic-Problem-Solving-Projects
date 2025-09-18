import java.io.File;
import java.util.Scanner;
import java.io.FileWriter;
import java.util.Vector;
import java.util.HashMap;


public class App {
    static Vector<Integer> lzw_commpression(String Text) {
        Vector<String> Dictionary = new Vector<String>();
        for (int i=0;i<128;i++)
            Dictionary.addElement(""+(char)i);


        Vector<Integer> Result = new Vector<Integer>();

        int i=0;
        while (i<Text.length()) {
            String substr = "";
            int j=i+1;

            int found_at = -1;

            for (;j<=Text.length();j++) {
                substr = Text.substring(i, j);
                int k=0;
                boolean found = false;
                for (;k<Dictionary.size();k++) {
                    if (substr.equals(Dictionary.elementAt(k))) {
                        found_at = k;
                        found = true;
                        break;
                    }
                }

                if (!found || j==Text.length()) {
                    Dictionary.addElement(substr);

                    Result.addElement(found_at);
                    break;
                }
            }
            i = j-1;
            if (j==Text.length()) i=Text.length();
        }
        return Result;
    }


    static String lzw_decommpression(Vector<Integer> commpressed) {
        Vector<String> Dictionary = new Vector<String>();
        for (int i=0;i<128;i++)
        Dictionary.addElement(""+(char)i);

        String Result = "";

        String current = "";
        String prev = "";
        for (int i=0;i<commpressed.size();i++) {
            if (commpressed.elementAt(i)<Dictionary.size()) 
                current = Dictionary.elementAt(commpressed.elementAt(i));
            else 
                current = prev+prev.charAt(0);
                

            Result += current;

            if (i!=0)
            Dictionary.add(prev+current.charAt(0));

            prev = current;
        }
        return Result;
    }
    
    
    public static void main(String[] args) throws Exception {
        File dir = new File(System.getProperty("user.dir"));

        File file = new File(dir, "file2.txt");


        String Text = "";
        Scanner scan = new Scanner(file);
        while (scan.hasNextLine()) {
            Text+=scan.nextLine();
            Text+="\n";
        }
        scan.close();


        Vector <Integer> compressed = new Vector<>();
        compressed = lzw_commpression(Text);


        File compFile = new File(dir, "compressed.txt");
        compFile.createNewFile();
        FileWriter write = new FileWriter(compFile);
        for (int i=0;i<compressed.size();i++)
            write.write(compressed.get(i)+",");
        write.close();



        Text = "";
        scan = new Scanner(compFile);
        while (scan.hasNextLine()) 
            Text+=scan.nextLine();
        scan.close();


        File decompFile = new File(dir, "decompressed.txt");
        decompFile.createNewFile();


        compressed = new Vector<>();
        String[] numbers = Text.split(",");
        for (String s : numbers)
        compressed.addElement(Integer.valueOf(s));

        write = new FileWriter(decompFile);
        write.write(lzw_decommpression(compressed));
        write.close();
    }

}
