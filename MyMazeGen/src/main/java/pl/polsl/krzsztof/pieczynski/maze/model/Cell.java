/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pl.polsl.krzsztof.pieczynski.maze.model;

/**
 *  Represents single cell of a maze
 * @author Krzysiek
 */
public class Cell {

 
    int id;
    /**
     * x coordiante
     */
    int x;
    /**
     * y coordinate
     */
    int y;
    //walls
    boolean up;
    boolean down;
    boolean left;
    boolean right;
    boolean visited = false;
   
    /**
     * Cinstructs and initializes cell
     * @param id
     * cell identyficator
     * @param x
     * x coordinate
     * @param y
     * y coordinate
     * @param up
     * up wall
     * @param down
     * down wall
     * @param left
     * left wall
     * @param right 
     * right wall
     */
    public Cell(int id,int x,int y, boolean up, boolean down, boolean left, boolean right)
    {
        this.id = id;
        this.x = x;
        this.y = y;
        this.up = up;
        this.down = down;
        this.left = left;
        this.right = right;
    }

        /**
     * checks if cell is in default state
     * @return 
     * true if cell is in default state
     */
    public boolean isDefault()
    {
        if(up == true && right == true && down==true && left == true && visited == false )
            return true;
        return false;
    }
    
    
    /**
     * Sets all walls to active
     */
    public void resetWalls()
    {
         this.up = true;
        this.down = true;
        this.left = true;
        this.right = true;
    }
    
    public void setVisited(boolean visited) {
        this.visited = visited;
    }
    
    
  public void setUp(boolean up) {
        this.up = up;
    }

    public void setDown(boolean down) {
        this.down = down;
    }

    public void setLeft(boolean left) {
        this.left = left;
    }

    public void setRight(boolean right) {
        this.right = right;
    }

    
    public int getId() {
        return id;
    }

    public boolean isVisited() {
        return visited;
    }

   
   
     public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }
    
    public boolean isUp() {
        return up;
    }

    public boolean isDown() {
        return down;
    }

    public boolean isLeft() {
        return left;
    }

    public boolean isRight() {
        return right;
    }         
    
}
