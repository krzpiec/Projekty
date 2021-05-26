/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pl.polsl.krzsztof.pieczynski.maze.model;

/**
 * Represents time results of given algorithm
 *
 * @author Krzysiek
 */
public class AlgorithmEfficiencyData {

    private String name;
    private float time;
    private int pathLength;

    AlgorithmEfficiencyData(String name, float time, int pathLength) {
        this.name = name;
        this.time = time;
        this.pathLength = pathLength;
    }

}
