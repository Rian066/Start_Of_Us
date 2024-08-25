import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

public class SnakeAtributes extends JPanel{
    
    private class Tile{
        int x;
        int y;

        Tile(int x, int y){
        this.x = x;
        this.y = y;
        }
    }

    int tileSize = 20;
    int height;
    int width;

    Tile snakeHead;

    SnakeAtributes(int height, int width){
        this.height = height;
        this.width = width;
        setPreferredSize(new Dimension(this.width, this.height));
        setBackground(Color.cyan);

    // Random number generator 
    Random rand = new Random();

    // Snake head position in terms of tiles
    snakeHead = new Tile(rand.nextInt(width/tileSize), rand.nextInt(height/tileSize));

      }

    public void paintComponent(Graphics g){
        super.paintComponent(g);
        draw(g);
    }

    public void draw(Graphics g){
        // Create Grid 
        for (int i = 0; i < width/tileSize; i++){
            g.drawLine(i * tileSize, 0, i * tileSize, height); // First point is every tile size (30 pixels) and end point is the end of the grid going down which is the height
            g.drawLine(0, i * tileSize, width, i * tileSize);  // First point is every tile size (30 pixels) and end point is the end of the grid going right which is the width
        }

        // Snake head visual
        g.setColor(Color.black);
        g.fillRect(snakeHead.x * tileSize, snakeHead.y * tileSize, tileSize, tileSize);
    }
}
