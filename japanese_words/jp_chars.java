import java.util.ArrayList;
import java.io.File;
import java.util.Scanner;
import java.io.FileNotFoundException;

public class jp_chars {

    public static ArrayList<String> readJpFile(String filename) {
        
        ArrayList<String> jp_words = new ArrayList<String>();

        if (filename == null) {return null;}

        try {
            File fileObj = new File(filename);
            Scanner fileReader = new Scanner(fileObj);
            while (fileReader.hasNextLine()) {
                String data = fileReader.nextLine();
                jp_words.add(data);
            }
            fileReader.close();
            return jp_words;
        } catch (FileNotFoundException e) {
            System.out.println("Cannot find file");
            e.printStackTrace();
            return null;
        }
    }

    public static void main(String[] args) {

        ArrayList<String> jp_words = readJpFile("common_words.txt");

        // for (String i : jp_words) {
        //     System.out.println(i);
        // }

        // System.out.println(jp_words.get(1));

        /* 
                    0	1	2	3	4	5   6  7   8   9   A  B	  C	  D	  E	  F
            U+304x		ぁ	あ	ぃ	い	ぅ	う	ぇ	え	ぉ	お	か	が	き	ぎ	く
            U+305x	ぐ	け	げ	こ	ご	さ	ざ	し	じ	す	ず	せ	ぜ	そ	ぞ	た
            U+306x	だ	ち	ぢ	っ	つ	づ	て	で	と	ど	な	に	ぬ	ね	の	は
            U+307x	ば	ぱ	ひ	び	ぴ	ふ	ぶ	ぷ	へ	べ	ぺ	ほ	ぼ	ぽ	ま	み
            U+308x	む	め	も	ゃ	や	ゅ	ゆ	ょ	よ	ら	り	る	れ	ろ	ゎ	わ
            U+309x	ゐ	ゑ	を	ん	ゔ	ゕ	ゖ			゙	   ゚    ゛	 ゜	ゝ	ゞ	ゟ
        */

        char iUnicode = '\u3044';
        char tsuUnicode = '\u3064';

        String whenString = String.valueOf(iUnicode) + String.valueOf(tsuUnicode);

        for (String i : jp_words) {
            if (i.contains(" " + whenString + " ")) {
                System.out.println(i);
            }
        }

        return;
    }
} 