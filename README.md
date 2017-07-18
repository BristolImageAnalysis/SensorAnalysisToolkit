# Preliminary instructions


```bash
git clone https://github.com/BristolImageAnalysis/SensorAnalysisToolkit.git
cd SensorAnalysisToolkit
vagrant up
vagrant ssh
source /cvmfs/sft.cern.ch/lcg/views/LCG_88/x86_64-slc6-gcc49-opt/setup.sh
cd /vagrant
mkdir build
cd build
cmake ../
make -j2

```
