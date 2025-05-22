import pandas as pd
import matplotlib.pyplot as plt
data = pd.read_csv("/Users/pierrickdubreuil/Library/Mobile Documents/com~apple~CloudDocs/Documents/INSA/Cours/4ème Année/Semestre printemps/Du capteur au banc de test/Projet/4GP-DUBREUIL-HOLM-TRUONG/4GP-DUBREUIL-HOLM-TRUONG/Resultats/Tests/test.csv", quotechar='"')


data["timestamp(ms)"] = data["timestamp(ms)"].astype(float)
data["graphite"] = data["graphite"].astype(int)

data["time_s"] = (data["timestamp(ms)"]-data["timestamp(ms)"].iloc[0])

plt.figure(figsize=(10,5))
plt.plot(data["time_s"], data["graphite"], label= "Données brutes")
plt.xlabel("Temps (s)")
plt.ylabel("Valeur graphite")
plt.title("Variation de la résistance graphite")
plt.grid(True)
plt.legend()
plt.show()

# 5. Lissage simple (moyenne glissante)
data["graphite_lissé"] = data["graphite"].rolling(window=3, center=True).mean()

# 6. Dérivée (variation entre points)
data["variation"] = data["graphite"].diff()

# 7. Tracé brut + lissé
plt.figure(figsize=(10, 5))
plt.plot(data["time_s"], data["graphite"], label="Brut", alpha=0.5)
plt.plot(data["time_s"], data["graphite_lissé"], label="Lissé", color='orange')
plt.xlabel("Temps (s)")
plt.ylabel("Signal graphite")
plt.title("Signal graphite - brut et lissé")
plt.grid(True)
plt.legend()
plt.show()

# 8. Tracé des variations (dérivée)
plt.figure(figsize=(10, 4))
plt.plot(data["time_s"], data["variation"], label="Variation", color='red')
plt.axhline(0, linestyle='--', color='gray')
plt.xlabel("Temps (s)")
plt.ylabel("Variation")
plt.title("Détection des flexions")
plt.grid(True)
plt.legend()
plt.show()