import java.util.Collections;
import java.util.Vector;
import java.io.*;
import java.nio.file.Files;
import java.math.BigDecimal;
import java.math.MathContext;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.Map;

class Frame extends JFrame implements ActionListener {
    JPanel panel;
    JTextField file_path;
    JButton browse;
    JFileChooser fileChooser;
    JButton Compress;
    JButton Decompress;
    JButton Exit;

    Frame() {
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setTitle("float arithmetic coding");
        setSize(500, 500);
        setLocationRelativeTo(null);
        setVisible(true);

        panel = new JPanel();

        panel.add(new JLabel("Enter file path: "));

        file_path = new JTextField(System.getProperty("user.dir"));
        panel.add(file_path);

        browse = new JButton("Browse files");
        browse.addActionListener(this);
        panel.add(browse);

        Compress = new JButton("Compress");
        Compress.addActionListener(this);
        panel.add(Compress);

        Decompress = new JButton("Decompress");
        Decompress.addActionListener(this);
        panel.add(Decompress);

        Exit = new JButton("Exit");
        Exit.addActionListener(this);
        panel.add(Exit);

        fileChooser = new JFileChooser(System.getProperty("user.dir"));
        fileChooser.setVisible(false);
        fileChooser.addActionListener(this);
        panel.add(fileChooser);

        add(panel);
        setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getActionCommand() == "Browse files") {
            fileChooser.setCurrentDirectory(new File("C:\\"));
            fileChooser.setCurrentDirectory(new File(file_path.getText()));
            if (!fileChooser.isVisible())
                fileChooser.setVisible(true);
        } else if (e.getActionCommand() == "ApproveSelection") {
            file_path.setText(fileChooser.getSelectedFile().toPath().toString());
            fileChooser.setVisible(false);
        } else if (e.getActionCommand() == "CancelSelection") {
            fileChooser.setVisible(false);
        } else if (e.getActionCommand() == "Compress") {
            File file = new File(file_path.getText());
            if (file.isFile()) {
                try {
                    Vector<Symbol> symbols = new Vector<Symbol>();
                    String Text = App.read_Text_file(file, symbols);
                    

                    String filename = file.getName();

                    File compFile = new File(file.getParentFile(),
                            (filename.endsWith(".txt") ? filename.substring(0, filename.length() - 4) + "_compressed.bin"
                                    : filename));
                    compFile.delete();
                    compFile.createNewFile();

                    if (Text.equals("")) {
                        App.write_bin_in_file(compFile, new BigDecimal("0"), symbols);
                        return;
                    }

                    BigDecimal commpressed = App.float_commpression(Text, symbols);
                    App.write_bin_in_file(compFile, commpressed, symbols);
                    JOptionPane.showMessageDialog(this, "file is compressed successfully");
                } 
                catch (Exception ex) {
                    JOptionPane.showMessageDialog(this, ex.getClass().getName());
                }
                
            } else
                JOptionPane.showMessageDialog(this, "the path entered is not a file");
        } else if (e.getActionCommand() == "Decompress") {
            File file = new File(file_path.getText());
            if (file.isFile()) {
                try {
                Vector<Symbol> symbols = new Vector<Symbol>();
                BigDecimal commpressed = App.read_bin_file(file, symbols);

                String Text = App.float_decommpression(commpressed, symbols);

                String filename = file.getName();
                File decompFile = new File(file.getParentFile(),
                        (filename.endsWith("_compressed.bin")
                                ? filename.substring(0, filename.length() - 15) + "_decompressed.txt"
                                : filename));
                decompFile.delete();
                
                decompFile.createNewFile();
                App.write_Text_in_file(decompFile, Text);
                JOptionPane.showMessageDialog(this, "file is decompressed successfully");
                } catch (Exception ex) {
                    String type = ex.getClass().getName();
                    if (type == "java.io.EOFException")
                    JOptionPane.showMessageDialog(this, "The file is not in the compressed format");
                    else
                    JOptionPane.showMessageDialog(this, type);
                }
                
            } else
                JOptionPane.showMessageDialog(this, "the path entered is not a file");
        } else if (e.getActionCommand() == "Exit") {
            System.exit(0);
        } else {
            System.out.println(e.getActionCommand());
        }
    }
}

class Symbol implements Comparable<Symbol> {
    char ch;
    int frequency;
    BigDecimal lower;
    BigDecimal upper;

    Symbol(char s) {
        ch = s;
        frequency = 1;
        lower = new BigDecimal(0);
        upper = new BigDecimal(1);
    }

    public int compareTo(Symbol other) {
        return Character.compare(this.ch, other.ch);
    }
}

public class App {

    static String read_Text_file(File file, Vector<Symbol> symbols) {
        String Text = "";
        try {
            Text = Files.readString(file.toPath());
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return e.getMessage();
        }
        for (int i = 0; i < Text.length(); i++) {
            if ((Text.charAt(i)) == '\r')
                i++;

            boolean found = false;
            for (int j = 0; j < symbols.size(); j++) {
                if (Text.charAt(i) == symbols.get(j).ch) {
                    found = true;
                    symbols.get(j).frequency++;
                    break;
                }
            }
            if (!found)
                symbols.addElement(new Symbol(Text.charAt(i)));

        }
        Collections.sort(symbols);
        return Text;
    }

    static BigDecimal read_bin_file(File file, Vector<Symbol> symbols) throws Exception {
        DataInputStream DataInputStream = new DataInputStream(new FileInputStream(file));
        int no_symbols = DataInputStream.readInt();
        while (!symbols.isEmpty())
            symbols.removeLast();

        for (int i = 0; i < no_symbols; i++) {
            Symbol s = new Symbol(DataInputStream.readChar());
            s.frequency = DataInputStream.readInt();
            symbols.addElement(s);
        }

        String s = DataInputStream.readUTF();
        BigDecimal bin = new BigDecimal(s);
        DataInputStream.close();
        return bin;
        
    }

    static void write_Text_in_file(File file, String Text) {
        try {
            FileWriter writer = new FileWriter(file);
            writer.write(Text);
            writer.close();
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return;
        }

    }

    static void write_bin_in_file(File file, BigDecimal compressed, Vector<Symbol> symbols) {
        try {
            DataOutputStream output = new DataOutputStream(new FileOutputStream(file));
            output.writeInt(symbols.size());
            for (Symbol s : symbols) {
                output.writeChar(s.ch);
                output.writeInt(s.frequency);
            }
            output.writeUTF(compressed.toString());
            output.close();
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return;
        }
    }

    public static Vector<Symbol> setupRanges(Vector<Symbol> symbols) {
        int total = 0;
        for (Symbol symbol : symbols) {
            total += symbol.frequency;
        }

        symbols.sort((s1, s2) -> Integer.compare(s2.frequency, s1.frequency));
        BigDecimal cprobability = new BigDecimal(0);
        for (Symbol symbol : symbols) {

            // System.out.println(symbol.ch + " :-");
            // System.out.println("Lower: " + cprobability);
            symbol.lower = cprobability;
            BigDecimal f = new BigDecimal(symbol.frequency);
            BigDecimal probability = f.divide(new BigDecimal(total),  MathContext.DECIMAL128);
            cprobability = cprobability.add(probability);
            // System.out.println("upper: " + cprobability);
            symbol.upper = cprobability;
            // System.out.println("__________________________________");
        }

        return symbols;
    }

    static BigDecimal float_commpression(String Text, Vector<Symbol> symbols) {
        symbols = setupRanges(symbols);
        Map<Character, Symbol> symbolsMap = new HashMap<>();
        for (Symbol s : symbols) {
            // System.out.println(s.ch + " lower :- " + s.lower + " upper :- " + s.upper);
            symbolsMap.put(s.ch, s);
        }
        BigDecimal lower = symbolsMap.get(Text.charAt(0)).lower;
        BigDecimal upper = symbolsMap.get(Text.charAt(0)).upper;
        // System.out.println("first lower: " + lower + " first upper: " + upper);
        BigDecimal range = upper.subtract(lower);

        for (int i = 1; i < Text.length(); i++) {
            if ((Text.charAt(i)) == '\r')
                i++;

            Symbol s = symbolsMap.get(Text.charAt(i));
            upper = lower.add(range.multiply(s.upper));
            lower = lower.add(range.multiply(s.lower));
            range = upper.subtract(lower);
            // System.out.println(Text.charAt(i) + " lower " + lower + " ,upper " + upper);
        }

        return (upper.add(lower)).divide(new BigDecimal(2));
    }

    static String float_decommpression(BigDecimal commpressed, Vector<Symbol> symbols) {
        BigDecimal lower= new BigDecimal(0);
        BigDecimal upper= new BigDecimal(1);

        // get accumlative frequencies;
        Vector<BigDecimal> acc_frequencies = new Vector<BigDecimal>();
        int no_symbols  = 0;
        acc_frequencies.addElement(new BigDecimal(0));
        for (Symbol s : symbols) 
            no_symbols+= s.frequency;
        BigDecimal current = new BigDecimal(0);
        for (Symbol s : symbols) {
            s.lower = current;
            BigDecimal f = new BigDecimal(s.frequency);
            BigDecimal probability = f.divide(new BigDecimal(no_symbols),  MathContext.DECIMAL128);
            current = current.add(probability);
            s.upper = current;
            acc_frequencies.addElement(current);
        }

        String Text = "";
        int counter = 0;
        while (counter < no_symbols) {
            for (Symbol symbol : symbols) {
                BigDecimal range = upper.subtract(lower);
                if ((commpressed.compareTo(lower.add(range.multiply(symbol.upper))) <= 0) && commpressed.compareTo(lower.add(range.multiply(symbol.lower))) >= 0) {
                    Text += symbol.ch;
                    upper = lower.add(range.multiply(symbol.upper));
                    lower = lower.add(range.multiply(symbol.lower));
                    break;
                }
            }
            counter++;
        }
        return Text;
    }

    public static void main(String[] args) throws Exception {
        new Frame();    
    }
}
