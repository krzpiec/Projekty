/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pl.polsl.krzsztof.pieczynski.maze.model;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author Krzysiek
 */
public class User {

    private String name;
    private List<AlgorithmEfficiencyData> usedAlgorithms;

    public User(String name) {
        this.name = name;
        this.usedAlgorithms = new ArrayList<>();
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public List<AlgorithmEfficiencyData> getUsedAlgorithms() {
        return usedAlgorithms;
    }

    /**
     * Adds algorithm and its work results to the list
     *
     * @param name name of the algorithm
     * @param time time of working
     * @param pathLength number of cells in path from start to end
     */
    public void addAlgorithmData(String name, float time, int pathLength) {
        this.usedAlgorithms.add(new AlgorithmEfficiencyData(name, time, pathLength));
    }

}
