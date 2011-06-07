reporte.pdf: *.tex reporte.bbl 
	latex reporte
	latex reporte

reporte.bbl: reporte.tex bibliografia.bib
	latex reporte
	bibtex reporte

clean:
	rm *.toc *.aux *.blg *.bbl *.pdf *.log
