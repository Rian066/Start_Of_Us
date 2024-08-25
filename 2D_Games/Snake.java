import javax.swing.*;

public class Snake {
    public static void main(String[] args) throws Exception {
      
      int height = 600;
      int width = 600;

      JFrame frame = new JFrame("Snake");
      frame.setVisible(true);
      frame.setSize(height, width);
      frame.setLocationRelativeTo(null);
      frame.setResizable(false);
      frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

      SnakeAtributes snakeAtb = new SnakeAtributes(height, width);
      frame.add(snakeAtb);
      frame.pack();
    }
  }