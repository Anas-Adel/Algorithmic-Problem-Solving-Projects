
import java.io.*;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;
import java.util.ArrayList;
import java.util.Arrays;

class Frame extends JFrame implements ActionListener {
    JPanel panel;
    JTextField file_path;
    JTextField block_size;
    JTextField code_book_size;
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

        panel.add(new JLabel("block size: "));
        block_size = new JTextField(5);
        panel.add(block_size);

        panel.add(new JLabel("code book size: "));
        code_book_size = new JTextField(5);
        panel.add(code_book_size);

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
                    // get input data
                    BufferedImage image = ImageIO.read(file);
                    int blockSize = Integer.parseInt(block_size.getText());
                    int codebookSize = Integer.parseInt(code_book_size.getText());

                    // Convert image to 2d array
                    int[][] pixels = new int[image.getHeight()][image.getWidth()];
                    for (int i = 0; i < image.getHeight(); i++) {
                        for (int j = 0; j < image.getWidth(); j++) {
                            pixels[i][j] = image.getRGB(j, i) & 0xFF; // Extract grayscale value
                        }
                    }

                    // compress
                    ArrayList<int[]> blocks = App.divideIntoBlocks(pixels, blockSize);
                    ArrayList<int[]> codebook = App.generateCodebook(blocks, codebookSize);
                    int[] compressedData = App.compress(blocks, codebook);

                    // create compression file
                    String filename = file.getName();
                    File compFile = new File(file.getParentFile(),
                            (filename.endsWith(".jpg")
                                    ? filename.substring(0, filename.length() - 4) + "_compressed.bin"
                                    : filename));
                    compFile.delete();
                    compFile.createNewFile();

                    // write data in compression file
                    DataOutputStream output = new DataOutputStream(new FileOutputStream(compFile));
                    output.writeInt(compressedData.length);
                    for (int i = 0; i < compressedData.length; i++) {
                        output.writeInt(compressedData[i]);
                    }
                    output.writeInt(codebookSize);
                    output.writeInt(blockSize);
                    for (int i = 0; i < codebookSize; i++) {
                        int[] block = codebook.get(i);
                        for (int j = 0; j < blockSize * blockSize; j++) {
                            output.writeInt(block[j]);
                        }
                    }
                    output.writeInt(pixels.length);
                    output.writeInt(pixels[0].length);
                    output.close();
                    JOptionPane.showMessageDialog(this, "file is compressed successfully");
                } catch (Exception ex) {
                    JOptionPane.showMessageDialog(this, ex.getClass().getName());
                    ex.printStackTrace();
                }

            } else
                JOptionPane.showMessageDialog(this, "the path entered is not a file");
        } else if (e.getActionCommand() == "Decompress") {
            File file = new File(file_path.getText());
            if (file.isFile()) {
                try {
                    // read compressed data from file
                    DataInputStream DataInputStream = new DataInputStream(new FileInputStream(file));
                    int compressed_size = DataInputStream.readInt();
                    int[] compressedData = new int[compressed_size];
                    for (int i = 0; i < compressed_size; i++) {
                        compressedData[i] = DataInputStream.readInt();
                    }
                    int codebookSize = DataInputStream.readInt();
                    int blockSize = DataInputStream.readInt();
                    ArrayList<int[]> codebook = new ArrayList<int[]>();
                    for (int i = 0; i < codebookSize; i++) {
                        int[] block = new int[blockSize * blockSize];
                        for (int j = 0; j < blockSize * blockSize; j++) {
                            block[j] = DataInputStream.readInt();
                        }
                        codebook.add(block);
                    }
                    int length = DataInputStream.readInt();
                    int width = DataInputStream.readInt();
                    DataInputStream.close();

                    // decompress
                    int[][] decompressedPixels = App.decompress(compressedData, codebook, length, width, blockSize);

                    // create decompression file
                    String filename = file.getName();
                    File decompFile = new File(file.getParentFile(),
                            (filename.endsWith("_compressed.bin")
                                    ? filename.substring(0, filename.length() - 15) + "_decompressed.jpg"
                                    : filename));
                    decompFile.delete();
                    decompFile.createNewFile();

                    // write data to decompression file
                    BufferedImage outputImage = new BufferedImage(width, length, BufferedImage.TYPE_BYTE_GRAY);
                    for (int i = 0; i < decompressedPixels.length; i++) {
                        for (int j = 0; j < decompressedPixels[0].length; j++) {
                            int gray = decompressedPixels[i][j];
                            int rgb = (gray << 16) | (gray << 8) | gray;
                            outputImage.setRGB(j, i, rgb);
                        }
                    }
                    ImageIO.write(outputImage, "jpg", decompFile);
                    JOptionPane.showMessageDialog(this, "file is decompressed successfully");
                } catch (Exception ex) {
                    String type = ex.getClass().getName();
                    if (type == "java.io.EOFException")
                        JOptionPane.showMessageDialog(this, "The file is not in the compressed format");
                    else
                        JOptionPane.showMessageDialog(this, type);
                    ex.printStackTrace();
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

public class App {
    public static void main(String[] args) {
        new Frame();
    }

    public static ArrayList<int[]> divideIntoBlocks(int[][] image, int blockSize) {
        ArrayList<int[]> blocks = new ArrayList<>();
        int rows = image.length;
        int cols = image[0].length;
        for (int i = 0; i < rows; i += blockSize) {
            for (int j = 0; j < cols; j += blockSize) {
                int[] block = new int[blockSize * blockSize];
                int index = 0;
                for (int x = 0; x < blockSize; x++) {
                    for (int y = 0; y < blockSize; y++) {
                        int row = i + x;
                        int col = j + y;
                        block[index++] = (row < rows && col < cols) ? image[row][col] : 0;
                    }
                }
                blocks.add(block);
            }
        }
        return blocks;
    }

    public static ArrayList<int[]> generateCodebook(ArrayList<int[]> blocks, int codebookSize) {
        int blockLen = blocks.get(0).length;
        ArrayList<int[]> codebooks = new ArrayList<>();
        int[] initialAverage = calculateAverage(blocks);
        codebooks.add(initialAverage);
        // split
        while (codebooks.size() < codebookSize) {
            ArrayList<int[]> newCodebook = new ArrayList<>();
            for (int[] codebook : codebooks) {
                int[] c1 = Arrays.copyOf(codebook, blockLen);
                int[] c2 = Arrays.copyOf(codebook, blockLen);
                for (int i = 0; i < blockLen; i++) {
                    c1[i] -= 1;
                    c2[i] += 1;
                }
                newCodebook.add(c1);
                newCodebook.add(c2);
            }
            codebooks = updateCodebook(blocks, newCodebook);
        }
        return codebooks;
    }

    private static int[] calculateAverage(ArrayList<int[]> blocks) {
        int blockLen = blocks.get(0).length;
        int[] average = new int[blockLen];
        for (int[] block : blocks) {
            for (int i = 0; i < blockLen; i++) {
                average[i] += block[i];
            }
        }
        for (int i = 0; i < blockLen; i++) {
            average[i] /= blocks.size();
        }
        return average;
    }

    private static ArrayList<int[]> updateCodebook(ArrayList<int[]> blocks, ArrayList<int[]> newCodebook) {
        int blockLen = blocks.get(0).length;
        int[] count = new int[newCodebook.size()];
        int[][] sums = new int[newCodebook.size()][blockLen];

        // get the nearest blocks
        for (int[] block : blocks) {
            int nearestIndex = 0;
            double minDistance = Double.MAX_VALUE;
            for (int i = 0; i < newCodebook.size(); i++) {
                double distance = calculateDistance(block, newCodebook.get(i));
                if (distance < minDistance) {
                    minDistance = distance;
                    nearestIndex = i;
                }
            }
            count[nearestIndex]++;
            for (int i = 0; i < blockLen; i++) {
                sums[nearestIndex][i] += block[i];
            }
        }

        // recalculate the average
        ArrayList<int[]> updatedCodebook = new ArrayList<>();
        for (int i = 0; i < newCodebook.size(); i++) {
            if (count[i] > 0) {
                int[] newValues = new int[blockLen];
                for (int j = 0; j < blockLen; j++) {
                    newValues[j] = sums[i][j] / count[i];
                }
                updatedCodebook.add(newValues);
            }
        }

        return updatedCodebook;
    }

    public static int[] compress(ArrayList<int[]> blocks, ArrayList<int[]> codebook) {
        int[] compressedData = new int[blocks.size()];
        for (int i = 0; i < blocks.size(); i++) {
            int bestIndex = 0;
            double bestDistance = Double.MAX_VALUE;
            for (int j = 0; j < codebook.size(); j++) {
                double distance = calculateDistance(blocks.get(i), codebook.get(j));
                if (distance < bestDistance) {
                    bestDistance = distance;
                    bestIndex = j;
                }
            }
            compressedData[i] = bestIndex;
        }
        return compressedData;
    }

    public static int[][] decompress(int[] compressedData, ArrayList<int[]> codebook, int rows, int cols,
                                     int blockSize) {
        int[][] decompressedImage = new int[rows][cols];
        int blockIndex = 0;
        for (int i = 0; i < rows; i += blockSize) {
            for (int j = 0; j < cols; j += blockSize) {
                int[] block = codebook.get(compressedData[blockIndex++]);
                int index = 0;
                for (int x = 0; x < blockSize; x++) {
                    for (int y = 0; y < blockSize; y++) {
                        int row = i + x;
                        int col = j + y;
                        if (row < rows && col < cols) {
                            decompressedImage[row][col] = block[index++];
                        }
                    }
                }
            }
        }
        return decompressedImage;
    }

    public static double calculateDistance(int[] block1, int[] block2) {
        double sum = 0;
        for (int i = 0; i < block1.length; i++) {
            sum += Math.abs(block1[i] - block2[i]);
        }
        return sum;
    }
}
