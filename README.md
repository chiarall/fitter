
// Da eseguire nel terminale per compilare:

// Crea un dizionario che contiene tutte le classi aggiuntive e le salva dentro // macroDict.cxx

rootcint -f macroDict.cxx -c PDF.h LinkDef.h




// Compila tutto e da macroDict.cxx prende le interfacce delle classi aggiuntive
// Alla fine crea l'eseguibile PDF

g++ `root-config --cflags --glibs` -L $ROOTSYS/lib -L $ROOTSYS/include -lRooFitCore -lRooFit -o PDF fitter.C PDF.cxx macroDict.cxx

// Lancia la macro
./PDF
