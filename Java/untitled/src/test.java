import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.OpenOption;
import java.nio.file.Path;
import java.nio.file.Paths;

import static java.nio.file.StandardOpenOption.*;

public class test {
    public static void main(String[] args) {
        String FILENAME = "C:/Users/sungc/IdeaProjects/untitled/src/text.txt";
        String text = "heo\nnice to meet you\n this is test";
        Path path = Paths.get(FILENAME);
        Charset charset = Charset.forName("UTF-8");
        if (Files.exists(path)) {
            try (BufferedReader reader = Files.newBufferedReader(path, charset);
            BufferedWriter writer = Files.newBufferedWriter(path, charset, APPEND)) {
//                String line;
//                while ((line = reader.readLine()) != null) {
//                    System.out.println(line);
//                }
                writer.append(text);
            } catch (IOException e) {
                e.printStackTrace();
                System.out.println(e);
            } finally {

            }
        }
    }
}
