import javax.swing.*;

public class Snake {
    public static void main(String[] args) {
      
      int height = 600;
      int width = 600;

      JFrame frame = new JFrame("Snake");
      frame.setVisible(true);
      frame.setSize(height, width);
      frame.setLocation(null);
      frame.setResizable(false);
      frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
  }