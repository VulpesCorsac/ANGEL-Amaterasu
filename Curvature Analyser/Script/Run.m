NotebookPauseForEvaluation[nb_] := Module[{},
While[NotebookEvaluatingQ[nb],Pause[.25]]];

NotebookEvaluatingQ[nb_]:=Module[{},
SelectionMove[nb,All,Notebook];
Or@@Map["Evaluating"/.#&,Developer`CellInformation[nb]]
];

UsingFrontEnd[
nb = NotebookOpen["C:\\Users\\George\\Desktop\\Script\\CurvatureAnalyser_V2.2.5.nb"];
SelectionMove[nb, All, Notebook];
SelectionEvaluate[nb]
NotebookPauseForEvaluation[nb];
NotebookSave[nb];
];

Quit[];