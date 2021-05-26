/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pl.polsl.krzysztof.pieczynski.maze.view;

import java.awt.*;
import java.awt.event.ActionListener;
import java.util.List;
import java.util.ArrayList;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.table.DefaultTableModel;

/**
 * Represents vew of the maze
 * @author Krzysiek
 */
public class MazeView extends JFrame{
    
    
    private int FRAME_SIZE_X;
    private int FRAME_SIZE_Y;
    private int TILE_SIZE;
    private int offsetX;
    private int offsetY;
    private JButton generateMazeButton = new JButton("Generate maze");
    private JButton getStartPos = new JButton("Start position");
    private JButton getEndPos = new JButton("End position");
    private JButton solveButton = new JButton("Solve");
    private JButton clearMazeButton = new JButton("Clear maze");
    private JTable algorithmsTable = new JTable();
    private JButton getUserName = new JButton("Set your name");
    private JButton clearRandomWalls = new JButton("Delete random walls");
    
    
    
    
    JScrollPane algorithmsScroll = new JScrollPane(algorithmsTable);
    private String[] algoritmsNames = {"BFS-URDL", "BFS-DRLU", "ASTAR"};
    JComboBox algNamesBox = new JComboBox(algoritmsNames);
    String[] columns = {"Name", "ElapsedTime", "Path length"};
   //Object[][] defaultTableValue = {{"default", 10, 10}};
      DefaultTableModel model = new DefaultTableModel();
     Object[] row = new Object[3];
    
   // public JFrame frame;
    private JPanel panel;
    private JTextField startPosX = new JTextField(10);   
    private JTextField startPosY = new JTextField(10);
    private JTextField endPosX = new JTextField(10);
    private JTextField endPosY = new JTextField(10);
    
    private JTextField UserName = new JTextField(30);
     
     /**
      * Constructs and initializes view
      * @param TileSize
      * Size of a single tile
      * @param FrameSizeX
      * Size of the window in X axis
      * @param FrameSizeY
      * Size of the window in Y axis
      * @param offsetX 
      * Up-left maze corner X coordinate
      * @param offsetY
      * Up-left maze corner Y coordinate
      */
    public MazeView(int TileSize, int FrameSizeX, int FrameSizeY, int offsetX, int offsetY)
    {
        
        this.TILE_SIZE = TileSize;
        this.offsetX = offsetX;
        this.offsetY = offsetY;
        this.FRAME_SIZE_X = FrameSizeX;
        this.FRAME_SIZE_Y = FrameSizeY;
        
      this.panel=new JPanel();
      this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      this.panel.setLayout(null);
      setSize(FRAME_SIZE_X,FRAME_SIZE_Y );
      getContentPane().add(panel);
     
      initComponentsWithPositions();
      //algNamesBox.setSelectedIndex(0);
     
        
    }

    public int getTILE_SIZE() {
        return TILE_SIZE;
    }
    
    
    /**
     * Initializes all components and sets its posiition
     */
    private void initComponentsWithPositions()
    {
        
      generateMazeButton.setBounds(50, 325, 150, 50);
      panel.add(generateMazeButton);  
        
      clearRandomWalls.setBounds(50,400,150,50);
      panel.add(clearRandomWalls);
        
      
         
      solveButton.setBounds(50,475,150,50);
      panel.add(solveButton);
      
       algNamesBox.setBounds(75,550,100,50);
      panel.add(algNamesBox);
      
      clearMazeButton.setBounds(50, 625, 150,50);
      panel.add(clearMazeButton);
      
      getStartPos.setBounds(50,50,150,50);
      panel.add(getStartPos);
      
      startPosX.setBounds(250,50,100,50);
      startPosX.setToolTipText("X coordinate");
      panel.add(startPosX);
      
      startPosY.setBounds(400,50,100,50);
       startPosY.setToolTipText("Y coordinate");
      panel.add(startPosY);
     
      getEndPos.setBounds(50,125,150,50);
      panel.add(getEndPos);
      
      endPosX.setBounds(250,125,100,50);
      endPosX.setToolTipText("X coordinate");
      panel.add(endPosX);
      
      endPosY.setBounds(400,125,100,50);
       endPosY.setToolTipText("Y coordinate");
      panel.add(endPosY);
      
      getUserName.setBounds(550,90,150,50);
      panel.add(getUserName);
      
      UserName.setBounds(725,90,150,50);
      panel.add(UserName);
      
      
       
        model.setColumnIdentifiers(columns);
       
     algorithmsTable.setBounds(925, 25, 450,150);
      algorithmsTable.setPreferredScrollableViewportSize(new Dimension(450, 150));
      algorithmsTable.setFillsViewportHeight(true);
      Font font = new Font("",1,12);
        algorithmsTable.setFont(font);
        algorithmsTable.setRowHeight(30);
        algorithmsTable.setModel(model);
      
    
      panel.add(algorithmsTable);
      algorithmsScroll.setVisible(true);
      panel.add(algorithmsScroll);
      
    }
    
    /**
     * Adds new row for algorithm results table
     * @param name Name of an algorithm
     * @param elapsedTime Time of execution
     * @param pathSize Number of cells in path
     */
    public void addTableRow(String name, float elapsedTime, int pathSize)
    {
        row[0] = name;
        row[1] = elapsedTime;
        row[2] = pathSize;
        model.addRow(row);
    }
    
    /**
     * Renders every ten index for helping determine where put point /?????
     * @param W Max width of maze
     * @param H Max height of maze
     */
    public void renderIndexes(int W, int H)
    {
         Graphics g = getGraphics();
         int stepsX = (int)(W/10);
         int number = 0;
         for(int i=0;i<stepsX; i++)
         {
            g.drawString(Integer.toString(number), offsetX+number*10, offsetY-5);
            number+=10;
         }
         if((W-1)%10 != 0)
         {
               g.drawString(Integer.toString(W-1), offsetX+(W-1)*10, offsetY-5);
         }
       
         
         number = 0;
         int stepsY = (int)(H/10);
         for(int i=0;i<stepsY; i++)
         {
            g.drawString(Integer.toString(number), offsetX-15, offsetY+(number+1)*10);
            number+=10;
         }
         if((H-1)%10 != 0)
         {
             g.drawString(Integer.toString(H-1), offsetX-15, offsetY+(H-1)*10);
         }
         
         
    }
    
    
   /**
    * Renders particular cell
    * @param posX
    * x coordinate
    * @param posY
    * y coordinate
    * @param up
    * up wall
    * @param right
    * right wall
    * @param down
    * down wall
    * @param left 
    * left wall
    */
    
    public void renderCell(int posX, int posY, boolean up, boolean right, boolean down, boolean left)
    {
        Graphics g = getGraphics();
       
    
        
        //draw upper wall
        if(up)
        g.drawLine(posX + offsetX, posY + offsetY, posX + TILE_SIZE + offsetX, posY + offsetY);
        //draw right wall
         if(right)
        g.drawLine( posX + TILE_SIZE + offsetX, posY + offsetY, posX + TILE_SIZE + offsetX, posY + TILE_SIZE + offsetY);
        //draw bottom wall
         if(down)
        g.drawLine( posX + TILE_SIZE + offsetX, posY + TILE_SIZE + offsetY, posX + offsetX, posY + TILE_SIZE+ offsetY);
        //draw left wall
         if(left)
        g.drawLine( posX + offsetX, posY + offsetY+ TILE_SIZE , posX + offsetX, posY + offsetY);
    }
    
  
    /**
     * Renders circle inside the cell
     * @param x
     * x coordinate
     * @param y
     * y coordinate
     * @param color_switch 
     * determines which color have to be used
     */
    public void colorCell(int x, int y, int color_switch)
    {
        Graphics g = getGraphics();
          Graphics2D g2 = (Graphics2D) g;
          switch(color_switch)
          {
              case 0://path
                  g2.setColor(Color.red); 
                  break;
              case 1://start
                   g2.setColor(Color.green); 
                   break;
              case 2://end
                   g2.setColor(Color.blue);
                   break;
              default:
                  break;
          }
            
       
        g2.fillOval(
                x * TILE_SIZE + TILE_SIZE/4 + offsetX, y * TILE_SIZE + TILE_SIZE/4 + offsetY,
                TILE_SIZE/2, TILE_SIZE/2 );
       
    }
    /**
     * Shows dialog window with error message
     * @param errorMessage error message
     */
   public void displayErrorMessage(String errorMessage)
    {
        JOptionPane.showMessageDialog(this, errorMessage);
    }
    
   
   /**
    * Adds listener for changing username 
    * @param listenGenerateButton listener
    */
   public void addChengeNameListener(ActionListener listenGenerateButton)
    {
        getUserName.addActionListener(listenGenerateButton);
    }
   
   
    /**
     * Adds listener for GenerateMaze button
     * @param listenGenerateButton listener
     */
    public void addGenerateMazeListener(ActionListener listenGenerateButton)
    {
        generateMazeButton.addActionListener(listenGenerateButton);
    }
    /**
     * Adds listener for StartPos button
     * @param listenStartPos listener
     */
    public void addStartPosButtnoList(ActionListener listenStartPos)
    {
        getStartPos.addActionListener(listenStartPos);
    }
    /**
     * Adds listener for EndPos button
     * @param listenEndPos listener
     */
      public void addEndPosButtnoList(ActionListener listenEndPos)
    {
        getEndPos.addActionListener(listenEndPos);
    }
      
      /**
       * Adds listener for Solve button
       * @param listensolve listener
       */
       public void addSolvelist(ActionListener listensolve)
    {
        solveButton.addActionListener(listensolve);
    }
       /**
        * Adds listener for clearing maze
        * @param listenClearMaze 
        */
    public void addClearMazeButtonListener(ActionListener listenClearMaze)
    {
        clearMazeButton.addActionListener(listenClearMaze);
    }
      /**
       * Adds listener for algorithm select comboBox
       * @param listensolve listener
       */ 
     public void addAlgorithmNameBoxListener(ActionListener listensolve)
    {
        algNamesBox.addActionListener(listensolve);
    }   
       /**
        * Adds listener for deleting random walls
        * @param listenRandomWalls 
        */
     public void addDeleteRandomWallsListener(ActionListener listenRandomWalls)
     {
         clearRandomWalls.addActionListener(listenRandomWalls);
     }
     
       /**
        * Gets value from Username JTextField
        * @return New name of the user
        */
       public String getName()
       {
           if(UserName.getText() == "")
               return "default";
           return UserName.getText();
       }
       
       
       /**
        * Gets value from start_pos_X JTextField
        * @return
        * Returns typed x coordinate of starting point
        * if field is empty returns null
        */
    public int getStartPosX()
    {
        return Integer.parseInt(startPosX.getText());
    }
    /**
        * Gets value from start_pos_y JTextField
        * @return
        * Returns typed y coordinate of starting point
        * if field is empty returns null
        */
     public int getStartPosY()
    {
        return Integer.parseInt(startPosY.getText());
    }
    /**
        * Gets value from end_pos_X JTextField
        * @return
        * Returns typed x coordinate of ending point
        * if field is empty returns null
        */
      public int getEndPosX()
    {
        return Integer.parseInt(endPosX.getText());
    }
         /**
        * Gets value from end_pos_y JTextField
        * @return
        * Returns typed y coordinate of ending point
        * if field is empty returns null
        */
     public int getEndPosY()
    {
        return Integer.parseInt(endPosY.getText());
    }
    
     /**
      * Gets selected name from combobox
      * @return 
      * Returns selected algorithm name
      */
     
    public String getAlgorihtmName()
    {
        return (String)algNamesBox.getSelectedItem();
    }
     
     /**
      * Covers maze with background colored rectangle
      */
    public void clearScreen()
    {
       Graphics g = getGraphics();
       g.clearRect(offsetX, offsetY, FRAME_SIZE_X, FRAME_SIZE_X);
    }
    
    
}
