import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.BitSet;
import java.util.Collections;
import java.io.FileWriter;
import java.nio.file.Files;
import java.util.Vector;

class Symbol {
    char ch;
    int frequency;
    String bit_code;

    Symbol (char s) {
        ch = s;
        frequency = 1;
        bit_code = "";
    }

    public int compareTo(Symbol other) {
        return Integer.compare(this.frequency, other.frequency);
    }
}

class Node implements Comparable<Node>{
    public int frequency=0;
    public Symbol symbol=null;
    public Node left=null;
    public Node right=null;

    Node (int freq) {
        frequency = freq;
    }

    @Override
    public int compareTo(Node other) {
        return Integer.compare(this.frequency, other.frequency);
    }
}

public class App {
    static void set_bit_codes(Node node,String bit_code) {
        if (node == null)
        return;

        if (node.symbol == null) {
            set_bit_codes(node.left, bit_code+"0");
            set_bit_codes(node.right, bit_code+"1");
        }
        else {
            node.symbol.bit_code = bit_code;
        }
    }
    
    static BitSet huffman_compression(String Text, Vector<Symbol>symbols) {
        BitSet compressed = new BitSet();
        if (Text.equals("")) {
            compressed.set(0);
            return compressed;
        }

        Vector<Node> nodes = new Vector<Node>();
        // create leaf nodes
        for (Symbol s : symbols) {
            Node n = new Node(s.frequency);
            n.symbol = s;
            nodes.addElement(n);
        }
        // construct the rest of the tree
        while (nodes.size()>1) {
            Collections.sort(nodes);
            Node n = new Node(nodes.get(0).frequency+nodes.get(1).frequency);
            n.left = nodes.get(0);
            n.right = nodes.get(1);
            nodes.remove(0);
            nodes.set(0, n);
        }
        // set the bit codes for each symbol
        if (symbols.size() == 1) set_bit_codes(nodes.get(0), "0");
        else set_bit_codes(nodes.get(0), "");
        

        // convert symbols to it's bit codes
        int no_bits = 0;
        for (int i=0;i<Text.length();i++) {
            for (int j=0;j<symbols.size();j++) {
                if (Text.charAt(i) == symbols.elementAt(j).ch) {
                    String code = symbols.elementAt(j).bit_code;
                    for (int k=0;k<code.length();k++) {
                        if (code.charAt(k) == '1')
                        compressed.set(no_bits);

                        no_bits++;
                    }
                }
            }
        }
        compressed.set(no_bits);



        return compressed;
    }

    static String huffman_decompression(BitSet compressed, Vector<Symbol>symbols) {
        Vector<Node> nodes = new Vector<Node>();
        // create leaf nodes
        for (Symbol s : symbols) {
            Node n = new Node(s.frequency);
            n.symbol = s;
            nodes.addElement(n);
        }
        // construct the rest of the tree
        while (nodes.size()>1) {
            Collections.sort(nodes);
            Node n = new Node(nodes.get(0).frequency+nodes.get(1).frequency);
            n.left = nodes.get(0);
            n.right = nodes.get(1);
            nodes.remove(0);
            nodes.set(0, n);
        }
        // get no bits in file
        int no_bits = 0;
        for (int i=0;i<compressed.size();i++)
        if (compressed.get(i))
        no_bits = i;
        compressed.clear(no_bits);


        if (no_bits == 0) return "";



        String result="";

        Node symbol = nodes.get(0);
        for (int i = 0; i < no_bits; i++) {
            // System.out.println("bit " + i + 1 + ":- " + compressed.get(i));
            symbol = compressed.get(i) ? symbol.right : symbol.left;
            if (symbol.symbol != null) {
                result += symbol.symbol.ch;
                symbol = nodes.get(0);
            }
        }
        return result;
    }

    public static void main(String[] args) throws Exception {
        File dir = new File(System.getProperty("user.dir"));
        File file = new File(dir, "file.txt");

        // Read file.txt
        String Text = Files.readString(file.toPath());

        Vector<Symbol> symbols = new Vector<Symbol>();
        // get symbols and frequencies
        for (int i=0;i<Text.length();i++) {
            boolean found = false;
            for (int j=0;j<symbols.size();j++) {
                if (Text.charAt(i)==symbols.get(j).ch) {
                    found =true;
                    symbols.get(j).frequency++;
                    break;
                }
            }
            if (!found)
                symbols.addElement(new Symbol(Text.charAt(i)));
        }

            
        //compression
        BitSet compressed = huffman_compression(Text, symbols);
  

        // create a file called commpressed.bin
        File compFile = new File(dir, "compressed.bin");
        compFile.delete();
        compFile.createNewFile();

        // output the commpression to compression.bin
        DataOutputStream output = new DataOutputStream(new FileOutputStream("compressed.bin"));
        output.writeInt(symbols.size());
        for (Symbol s : symbols) {
            output.writeChar(s.ch);
            output.writeInt(s.frequency);
            
        }
        output.write(compressed.toByteArray());
        output.close();


/////////////////////////////////////////////////////////////////////////////////////////////////////////


        // Read compressed.bin
        DataInputStream DataInputStream = new DataInputStream(new FileInputStream("compressed.bin"));
        int no_symbols = DataInputStream.readInt();
        symbols = new Vector<Symbol>();
        for (int i=0;i<no_symbols;i++) {
            Symbol s = new Symbol(DataInputStream.readChar());
            s.frequency = DataInputStream.readInt();
            symbols.addElement(s);
        }
        compressed = BitSet.valueOf(DataInputStream.readAllBytes());
        DataInputStream.close();


        //decompression
        String decompressed = huffman_decompression(compressed, symbols);


        // write the result in decompressed.txt
        File decompFile = new File(dir, "decompressed.txt");
        decompFile.createNewFile();
        FileWriter writer = new FileWriter(decompFile);
        writer.write(decompressed);
        writer.close();
    }
}
