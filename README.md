# CPU Scheduling Simulation

C++ ile yazılmış, altı CPU zamanlama algoritmasını aynı veri seti üzerinde çalıştırıp karşılaştıran konsol programı. İşletim Sistemleri dersi kapsamında geliştirildi.

## Algoritmalar

| Algoritma | Tür |
|---|---|
| FCFS | - |
| SJF | Non-preemptive |
| SJF (SRTF) | Preemptive |
| Priority | Non-preemptive |
| Priority | Preemptive |
| Round Robin | Quantum = 4 |

## Girdi

Süreçler bir CSV dosyasından okunur (`case1.csv`):

```
Process_ID,Arrival_Time,CPU_Burst_Time,Priority
P001,0,4,high
P002,2,7,normal
P003,4,10,low
```

Öncelik değerleri `high`, `normal` ve `low` olarak verilir.

## Çıktı

Her algoritma için süreç başına bekleme süresi (WT, Waiting Time) ve çevrim süresi (TAT, Turnaround Time) ile bunların ortalamaları yazdırılır.

## Derleme ve çalıştırma

```
g++ -std=c++17 isletimsis.cpp -o scheduler
./scheduler
```

Program `case1.csv` dosyasını çalıştığı klasörden okur, bu yüzden repo klasöründe çalıştırılmalıdır.

## Örnek sonuçlar (`case1.csv`)

| Algoritma | Ort. WT | Ort. TAT |
|---|---|---|
| FCFS | 418 | 428.5 |
| SJF (Non-preemptive) | 268.39 | 278.89 |
| SJF (Preemptive / SRTF) | 267.86 | 278.36 |
| Priority (Non-preemptive) | 409.63 | 420.13 |
| Priority (Preemptive) | 411.39 | 421.89 |
| Round Robin (q=4) | 574.15 | 584.65 |

Bu veri setinde SJF ailesi en düşük ortalama bekleme süresini verir. SRTF, SJF'nin non-preemptive haline göre biraz daha iyidir. Round Robin en yüksek ortalama bekleme süresine sahiptir.
