import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class converter {


  public static void main(String[] args){

    try {
      File doc = new File("test.txt");
      Scanner S1 = new Scanner(doc);
      StringBuilder helper = new StringBuilder();

      while (S1.hasNextLine()){
        String line = S1.nextLine();
        line = line.replaceAll(" ", "");
        for(char each: line.toCharArray()){
          helper.append(each).append("\n");
        }
      }
      BufferedWriter writer = new BufferedWriter(new FileWriter("output.txt"));
      writer.write(helper.toString());
      writer.close();

    } catch(IOException ignored){

    }
  }


}
