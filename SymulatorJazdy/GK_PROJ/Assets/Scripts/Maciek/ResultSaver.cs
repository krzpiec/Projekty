using UnityEngine;

namespace Maciek
{
    public class ResultSaver : MonoBehaviour
    {
        private void Start()
        {
            RaceController.OnSpecificFinished += Save;
        }

        public static float Load(string raceName)
        {
            return PlayerPrefs.HasKey(raceName) ? PlayerPrefs.GetFloat(raceName) : 0f;
        }
        
        private void Save(string raceName)
        {
            if (PlayerPrefs.HasKey(raceName) && PlayerPrefs.GetFloat(raceName) < RaceController.ElapsedTime)
            {
                return;
            }
            
            PlayerPrefs.SetFloat(raceName, RaceController.ElapsedTime);
        }
    }
}