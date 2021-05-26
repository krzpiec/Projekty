using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class UpgradeManager : MonoBehaviour
{
    public float hidingOffset;
    public float buttonShowingSpeed;

    private bool engineButtonFlag;
    private bool wheelButtonFlag;
    private bool nitroButtonFlag;

    public Button engineButton;
    public Button wheelsButton;
    public Button nitroButton;

    public List<GameObject> engineUpgrades;
    public List<GameObject> wheelsUpgrades;
    public List<GameObject> nitroUpgrades;

    public List<GameObject> engineUpgradesInfo;

    public Button Accept;
    public Button Deny;

    bool upgradesBought = false; // zamienic na tablice;

    private int optionChoosen;

    private GameObject car;
  
    private void Start()
    {
        engineButtonFlag = false;
        foreach (Transform child in engineButton.transform)
        {
            engineUpgrades.Add(child.gameObject);
            child.gameObject.transform.position = engineButton.transform.position;     
            child.gameObject.SetActive(false);
        }

        wheelButtonFlag = false;
        foreach (Transform child in wheelsButton.transform)
        {
            wheelsUpgrades.Add(child.gameObject);
            child.gameObject.transform.position = wheelsButton.transform.position;
            child.gameObject.SetActive(false);
        }


        nitroButtonFlag = false;
        foreach (Transform child in nitroButton.transform)
        {
            nitroUpgrades.Add(child.gameObject);
            child.gameObject.transform.position = nitroButton.transform.position;
            child.gameObject.SetActive(false);
        }


        foreach(GameObject info in engineUpgradesInfo)
        {
            info.gameObject.SetActive(false);
        }

        Accept.gameObject.SetActive(false);
        Deny.gameObject.SetActive(false);
        car = GameObject.FindGameObjectWithTag("Player");
    }

    private void Update()
    {
        handleButtonApearing(engineButtonFlag, engineButton, engineUpgrades);
        handleButtonApearing(wheelButtonFlag, wheelsButton, wheelsUpgrades);
        handleButtonApearing(nitroButtonFlag, nitroButton, nitroUpgrades);
    }

    private void handleButtonApearing(bool flag, Button leadingButton, List<GameObject> upgrades)
    {
        if (flag)
        {
            foreach (GameObject button in upgrades)
            {
                float percentOfDistanceTravelled = (button.transform.position.x - leadingButton.transform.position.x + hidingOffset) / (button.GetComponent<DesiredButtonPosition>().DesiredButtonPos.x - leadingButton.transform.position.x + hidingOffset);
                button.transform.GetChild(0).GetComponent<Text>().color = new Color(percentOfDistanceTravelled, percentOfDistanceTravelled, percentOfDistanceTravelled, 1);
                button.GetComponent<Image>().color = new Color(percentOfDistanceTravelled, percentOfDistanceTravelled, percentOfDistanceTravelled, 1);
                button.transform.position = Vector3.Lerp(button.transform.position, button.GetComponent<DesiredButtonPosition>().DesiredButtonPos, buttonShowingSpeed * Time.deltaTime);
            }
        }
        else
        {
            foreach (GameObject button in upgrades)
            {
                float percentOfDistanceTravelled = (button.transform.position.x - leadingButton.transform.position.x + hidingOffset) / (button.GetComponent<DesiredButtonPosition>().DesiredButtonPos.x - leadingButton.transform.position.x + hidingOffset);
                percentOfDistanceTravelled -= 0.4f;
                if (percentOfDistanceTravelled < 0f)
                    percentOfDistanceTravelled = 0f;
                button.transform.GetChild(0).GetComponent<Text>().color = new Color(percentOfDistanceTravelled, percentOfDistanceTravelled, percentOfDistanceTravelled, 1);
                button.GetComponent<Image>().color = new Color(percentOfDistanceTravelled, percentOfDistanceTravelled, percentOfDistanceTravelled, 1);
                button.transform.position = Vector3.Lerp(button.transform.position, leadingButton.transform.position, buttonShowingSpeed * Time.deltaTime);
                if (button.transform.position.x < leadingButton.transform.position.x + hidingOffset)
                {
                    button.gameObject.SetActive(false);
                }
            }
        }
    }
   

    public void engineButtonPressed()
    {
        foreach (GameObject info in engineUpgradesInfo)
        {
            info.gameObject.SetActive(false);
        }
        if (!engineButtonFlag)
        {
            engineButton.GetComponent<Image>().color = Color.cyan;
            foreach(GameObject button in engineUpgrades)
            {
                button.gameObject.SetActive(true);
            }
        }
        else
        {
            engineButton.GetComponent<Image>().color = Color.white;
        }
        engineButtonFlag = !engineButtonFlag;
    }
    public void wheelsButtonPressed()
    {
        if (!wheelButtonFlag)
        {
            wheelsButton.GetComponent<Image>().color = Color.cyan;
            foreach (GameObject button in wheelsUpgrades)
            {
                button.gameObject.SetActive(true);
            }
        }
        else
        {
            wheelsButton.GetComponent<Image>().color = Color.white;
        }
        wheelButtonFlag = !wheelButtonFlag;

    }
    public void nitroButtonPressed()
    {
        if (!nitroButtonFlag)
        {
           nitroButton.GetComponent<Image>().color = Color.cyan;
            foreach (GameObject button in nitroUpgrades)
            {
                button.gameObject.SetActive(true);
            }
        }
        else
        {
            nitroButton.GetComponent<Image>().color = Color.white;
        }
        nitroButtonFlag = !nitroButtonFlag;

    }



    public void AcceptOnClick()
    {
        if(optionChoosen == 0 )
        {
            car.GetComponent<CarController>().motorTorqueMultiplier = 0f;
            engineUpgrades[0].GetComponent<Image>().color = Color.green;
            engineUpgradesInfo[0].GetComponent<Image>().color = Color.green;
            upgradesBought = true;
        }
        ConfimationButtons(false);
    }

    public void DenyOnClick()
    {
        foreach (GameObject info in engineUpgradesInfo)
        {
            info.gameObject.SetActive(false);
        }
        ConfimationButtons(false);
    }
    public void ConfimationButtons(bool state)
    {
        Accept.gameObject.SetActive(state);
        Deny.gameObject.SetActive(state);
    }

    public void engineUpgrade1()
    {
        ConfimationButtons(false);
        if (!upgradesBought)
        {
            engineUpgrades[0].GetComponent<Image>().color = Color.cyan;
            foreach (GameObject info in engineUpgradesInfo)
            {
                info.gameObject.SetActive(false);
            }
            engineUpgradesInfo[0].SetActive(true);
            optionChoosen = 0;
            ConfimationButtons(true);
        }
        foreach (GameObject info in engineUpgradesInfo)
        {
            info.gameObject.SetActive(false);
        }
        engineUpgradesInfo[0].SetActive(true);

    }
    public void engineUpgrade2()
    {
        ConfimationButtons(false);
        engineUpgrades[1].GetComponent<Image>().color = Color.cyan;
        foreach (GameObject info in engineUpgradesInfo)
        {
            info.gameObject.SetActive(false);
        }
        engineUpgradesInfo[1].SetActive(true);
        optionChoosen = 1;
        ConfimationButtons(true);
    }
}
