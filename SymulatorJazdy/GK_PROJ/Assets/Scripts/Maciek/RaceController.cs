using System;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

namespace Maciek
{
    public class RaceController : MonoBehaviour
    {
        public static event Action<string> OnSpecificFinished;
        public event Action OnBegan;
        
        [SerializeField] private RaceTrigger finishTrigger;
        [SerializeField] private RaceTrigger beginTrigger;
        [SerializeField] private string raceName;

        private List<RaceTrigger> currentTriggers = new List<RaceTrigger>();
        private static string currentRaceName = EmptyRaceName;
        private RaceTrigger[] raceTriggers;
        private float startTime;
        
        public static float ElapsedTime { get; private set; }
        
        private const string EmptyRaceName = "";
        
        private void Start()
        {
            raceTriggers = GetComponentsInChildren<RaceTrigger>();
            finishTrigger.OnTriggered += TryFinishing;
            beginTrigger.OnTriggered += TryBeginning;
            
            foreach (RaceTrigger raceTrigger in raceTriggers)
            {
                raceTrigger.OnSpecificTriggered += TryFinishing;
            }
        }

        private void Update()
        {
            if (IsActive())
            {
                RefreshTimer();
            }
        }

        private void RefreshTimer()
        {
            ElapsedTime = Time.time - startTime;
        }

        private void TryBeginning()
        {
            if (!IsAnyRaceActive())
            {
                Begin();
            }
        }

        private void TryFinishing()
        {
            if (CanFinish())
            {
                Finish();
            }
        }

        private void TryFinishing(RaceTrigger trigger)
        {
            if (currentTriggers.Contains(trigger))
            {
                return;
            }
            
            currentTriggers.Add(trigger);
            TryFinishing();
        }

        private bool IsAnyRaceActive()
        {
            return currentRaceName != EmptyRaceName;
        }

        private bool CanFinish()
        {
            return IsActive() && currentTriggers.Count + 1 == raceTriggers.Length;
        }
        
        private bool IsActive()
        {
            return currentRaceName == raceName;
        }

        private void Begin()
        {
            currentRaceName = raceName;
            currentTriggers?.Clear();
            startTime = Time.time;
            OnBegan?.Invoke();
        }

        private void Finish()
        {
            OnSpecificFinished?.Invoke(currentRaceName);
            currentRaceName = EmptyRaceName;
            ElapsedTime = 0f;
        }
    }
}