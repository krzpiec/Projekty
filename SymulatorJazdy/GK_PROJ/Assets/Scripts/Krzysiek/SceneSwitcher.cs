using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
public class SceneSwitcher : MonoBehaviour
{
    // Start is called before the first frame update
   public void backToDriving()
    {
        SceneManager.LoadScene("Krzyszsiek_Scene");
        GameObject.FindGameObjectWithTag("Player").GetComponent<CarController>().startVehicle();
        GameObject.FindGameObjectWithTag("Player").transform.position = new Vector3(-8f, 1f, 6f);
        GameObject.FindGameObjectWithTag("Player").transform.rotation = Quaternion.identity;
    }
}
