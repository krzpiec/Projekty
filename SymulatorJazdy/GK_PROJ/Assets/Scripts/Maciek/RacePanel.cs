using System;
using System.Collections;
using TMPro;
using UnityEngine;

namespace Maciek
{
    public class RacePanel : MonoBehaviour
    {
        [SerializeField] private TextMeshProUGUI resultContainer;
        [SerializeField] private TextMeshProUGUI timerContainer;

        private const int SecondsInMinute = 60;
        
        private void Start()
        {
            RaceController.OnSpecificFinished += PresentResult;
        }

        private void OnDestroy()
        {
            RaceController.OnSpecificFinished -= PresentResult;
        }

        private void Update()
        {
            timerContainer.text = DurationFor(RaceController.ElapsedTime);
        }

        private void PresentResult(string raceName)
        {
            StartCoroutine(C_PresentResult(raceName));
        }

        private IEnumerator C_PresentResult(string raceName)
        {
            resultContainer.text =
                $"Finished race {raceName} in time: {DurationFor(RaceController.ElapsedTime)}. Best time {DurationFor(ResultSaver.Load(raceName))}.";
            yield return new WaitForSeconds(2.5f);
            resultContainer.text = string.Empty;
        }

        private string DurationFor(float time)
        {
            return $"{time / SecondsInMinute:00}:{time % SecondsInMinute:00}";
        }
    }
}