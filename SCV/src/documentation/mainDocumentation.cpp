/*!
\mainpage SCV Documentation

O SCV � uma API (Application Programming Interface) de facilita��o na constru��o de interfaces de usu�rio (GUI - Graphic User Interface), orientada ao uso de um programador com experi�ncia na linguagem de programa��o C++. 

O SCV est� implementado sobre a API gr�fica OpenGL. Existe uma estrutura hier�rquica de componentes, onde cada componente � respons�vel por desenhar os componentes contidos nele. O componentes utilizam a fucionalidade de scissors do OpenGL para fazer a limita��o da �rea de desenho para apenas o ret�ngulo que engloba o componente, al�m de fazer o desenho dele mesmo, utilizando mapas de textura, compartilhados por todas as inst�ncias do mesmo tipo de componente, e fontes, representadas com uma textura contendo todos os caracteres, compartilhada em n�vel global. Esquemas de cor s�o implementados modulando-se a cor das texturas dos componentes. A intera��o entre componentes e o c�digo do usu�rio da biblioteca faz-se utilizando callbacks, presentes como fun��es virtuais nos componentes, que devem ser herdados.

Aqui voc� ir� encontrar a documenta��o de todos componentes e funcionalidades oferecidas. S�o disponibilizados tr�s manuais para o usu�rio:

- \subpage scv "SCV"
- \subpage desinger "SCV Desinger"
- \subpage freefrom "SCV Free Form Designer"


\section ide IDEs Suportadas
- Microsoft Visual Studio 2010
- g++ / makefile

A documenta��o atualizada poder� ser acessada atrav�s do endere�o: http://www-usr.inf.ufsm.br/~pozzer/scv <br/>
A �ltima vers�o da biblioteca poder� sempre ser encontrada em: http://www-usr.inf.ufsm.br/~pozzer/scv/scv_4.0.rar

\section home Get Started!

- Para acessar a documenta��o do SCV presente na pasta "documentation" execute o arquivo "Documentation.bat".
- Para visualizar v�rios exemplos utilizando o SCV e demonstrando suas funcionalidades execute o arquivo "SCV_Examples.bat".
- Para acessar o InterfaceDesginer execute o "InterfaceDesigner.bat", nele o usu�rio pode graficamente criar sua Interface, atrav�s de DragAndDrop, e gerar o c�digo SCV correspondente para o arquivo "interface.cpp".


\section credits Cr�ditos

- Prof. Cesar Tadeu Pozzer: Coordenador e Idealizador do Projeto
- Cicero Augusto de Lara Pahins: Desenvolvimento, Documenta��o
- Frederico Artur Limberger: Desenvolvimento, Documenta��o
- Leonardo Quatrin Campagnolo: Desenvolvimento, Documenta��o, Suporte
- Yuri Kunde Schlesner: Desenvolvimento, Documenta��o, Suporte
- Tiago Boelter Mizdal: Desenvolvimento, Documenta��o
- Eduardo Speroni  (vers�es anteriores do scv)
- Bernardo Henz
- Celito Much Felipetto 
- Vinicius Gottin

*/

/*************************************************************************************
/*************************************************************************************
/*************************************************************************************
/*************************************************************************************

/*! \page scv SCV
A estrutura de arquivos do SCV � apresentada na seguinte figura.  

 \image html images/diretorio.png

- Documentation: cont�m p�ginas HTML gerados pelo Doxygem com a documenta��o da API, e tamb�m manuais de uso da API e das ferramentas
- Lib: cont�m as libs usadas para compilar o SCV e as libs geradas a partir da compila��o do SCV
- Include: os arquivos de cabe�alho para compilar o SCV. 
- SCV: cont�m todo o c�digo fonte do SCV. Quando compilado, geras as libs (scv-debub e scv-release) que s�o necess�rias na compila��o dos demais projetos (os designers de interface e os exemplos)
- ExportedSource: armazena os arquivos gerados pelos designers de Interface
- UserProject: Pasta que cont�m um projeto para compila��o de aplicativos desenvolvidos com a API
- InterfaceDesigner: cont�m o c�digo do SCVDesigner, uma aplica��o desenvolvida para cria��o de interfaces com componentes redimension�veis . Para maiores detalhes da aplica��o, consultar o manual
- FreeFormInterfaceDesigner: semelhante ao InterfaceDesigner, � um aplica��o que permite a constru��o de interfaces gr�ficas do SVC que n�o tem o recurso de redimensionamento de componentes. 
- ExportedSource: projeto para compila��o dos c�digos-fonte gerados pelas aplica��es InterfaceDesigner e FreeFormInterfaceDesigner. 
- SCVExamples: Cont�m v�rios exemplos de aplicativos desenvolvidos com a API SCV, destacando o uso de widgets. 


O projeto scv.sln engloba 5 projetos Microsoft Visual Studio 10, que s�o descritos na sequencia. 
- InterfaceDesigner: cont�m o c�digo do SCVDesigner, uma aplica��o desenvolvida para cria��o de interfaces com componentes redimension�veis . Para maiores detalhes da aplica��o, consultar o manual
- FreeFormInterfaceDesigner: semelhante ao InterfaceDesigner, � um aplica��o que permite a constru��o de interfaces gr�ficas do SVC que n�o tem o recurso de redimensionamento de componentes. 
- ExportedSource: projeto para compila��o dos c�digos-fonte gerados pelas aplica��es InterfaceDesigner e FreeFormInterfaceDesigner. 
- SCV: projeto que cont�m todo o c�digo da API SCV. Quando executado, gera as libs do SCV. 
- SCVExamples: Cont�m v�rios exemplos de aplicativos desenvolvidos com a API SCV, destacando o uso de widgets. 

 \image html images/sln.png

 Para compilar uma aplica��o com o SCV deve-se adicionar 4 bibliotecas: Freeglut.lib, Freeimage.lib, Glew32.lib e Scv-debub.lib (ou scv-release.lib). Na interface do Visual Studio 2010, isso pode ser feito nos campos properties/VC++ Directories e  properties/Linker/Input, como mostrado nas seguintes figuras. Esta configura��o leva em considera��o a organiza��o de pastas do SCV. Isso pode ser modificado livremente pelo programador. 

 \image html images/include.png
 \image html images/lib.png

Para rodar os demos ou programas desenvolvidos no VS2010 em m�quinas que n�o tenham o VS, deve-se instalar tamb�m o Microsoft Visual C++ 2010 Redistributable. Sem ele, vem um aviso que faltam dlls para execu��o, mais especificamente as MSVCP100.dll e MSVCR100.dll.

O instalador da runtime pode ser baixado da Microsoft atrav�s deste link: http://www.microsoft.com/downloads/en/confirmation.aspx?familyid=A7B7A05E-6DE6-4D3A-A423-37BF0912DB84&displaylang=en

Outra op��o � simplesmente copiar essas duas DLLs do seu computador com VS para a pasta do exe. (Ficam em C:\\Windows\\System32\\msvcp100.dll e C:\\Windows\\System32\\msvcr100.dll)

\section references Trabalhos Publicados


PAHINS, C. A. L. Ambiente para constru��o de Interfaces gr�ficas de usu�rio com o SCV. Trabalho de Gradua��o em Ci�ncia da Computa��o, UFSM, 2011.

PAHINS, C. A. L.; POZZER, C. T. SCV - Simple Components for Visual. Jornada Acad�mica Integrada da Universidade Federal de Santa Maria, Santa Maria, RS, 2011.

PAHINS, C. A. L.; LIMBERGER, F. A.; HENZ, B.; SPERONI, E. A.; GOTTIN, V. M.; POZZER, C. T. Uma API Livre para Composi��o de GUI em Aplicativos Gr�ficos. F�rum Internacional de Software Livre 2010 - Workshop de Software Livre, Porto Alegre, RS, 2010.

PAHINS, C. A. L.; LIMBERGER, F. A.; POZZER, C. T. Uma Abordagem Gr�fica Utilizando o SCV. Jornada Acad�mica Integrada da Universidade Federal de Santa Maria, Santa Maria, RS, 2010.

PAHINS, C. A. L.; LIMBERGER, F. A.; HENZ, B.; POZZER, C. T. SCV: uma ferramenta para programa��o de aplicativos de interfaces gr�ficas. Congresso Regional de Inicia��o Cient�fica e Tecnol�gica em Engenharia, Rio Grande, RS, BR, 2010.

LIMBERGER, F. A.; PAHINS, C. A. L.; POZZER, C. T. SCV: uma ferramenta para programa��o de aplicativos de interfaces gr�ficas. Jornada Acad�mica Integrada da Universidade Federal de Santa Maria. Santa Maria, Santa Maria, RS, BR, 2010.

AVELAR, F. T.; GOMES, V. C. F.; POZZER, C. T. Estudo Comparativo de Bibliotecas Gr�ficas Integradas com OpenGL. XXII Congresso Regional de Inicia��o Cient�fica e Tecnol�gica em Engenharia - CRICTE, Passo Fundo, RS, 2007.

AVELAR, F. T.; GOMES, V. C. F.; POZZER, C. T. Estudo Comparativo de Bibliotecas Gr�ficas Integradas com OpenGL. XXII Congresso Regional de Inicia��o Cient�fica e Tecnol�gica em Engenharia - CRICTE, Passo Fundo, RS, 2007.

  
*/

 /*************************************************************************************
/*************************************************************************************
/*************************************************************************************
/*************************************************************************************
/*************************************************************************************

 
/*! \page designder SCV Designer 

O InterfaceDesigner � uma aplica��o que foi desenvolvida sobre a API SCV para agilizar a constru��o de interfaces gr�ficas usando a API SCV. Ela deve proporcionar ao usu�rio a possibilidade de arranjar os componentes gr�ficos da API SCV de maneira visual, oferecendo recursos para adi��o ou remo��o de objetos, exporta��o do c�digo resultante e alinhamento autom�tico de componentes relacionados por diferentes esquemas de organiza��o. Ele tamb�m pode ser usado como ferramenta para estudo das funcionalidades e sintaxe de c�digo do SCV, ou como ferramenta para constru��o da base da aplica��o para posterior expans�o manual com demais componentes.

Para maiores detalhes sobre a implementa��o do SCV e do SCV Designer, consulte (Pahins, 2011).

\section designinterface Interface

O SCV Designer apresenta uma estrutura modularizada, que possibilita a constru��o iterativa da interface do software. Ela apresenta 4 elementos b�sicos, como podem ser visualizados na seguinte Figura.

 \image html images/designer.png 

- DesignPreview: respons�vel pela pr�-visualiza��o em tempo real de interfaces produzidas pelo ambiente a partir da constru��o de uma visualiza��o aproximada, a qual busca refletir o resultado da exporta��o do trabalho realizado;

- GroupLayout: respons�vel pela constru��o hier�rquica de agrupamentos l�gicos para arranjo de componentes da API SCV;

- ObjectEditor: respons�vel pela edi��o de vari�veis e caracter�sticas, as quais estar�o presentes nas exporta��es do ambiente, de componentes da API SCV;

 \image html images/custonclass.png

- Code Viewer: respons�vel pela exporta��o do resultado produzido pelo ambiente de acordo com par�metros do usu�rio. S�o sempre exibidos 5 arquivos de c�digo fonte em Linguagem C++ que representam os componentes e regras de arranjo de componentes.


\section Cria��o de Interfaces

Para se criar uma interface gr�fica no SCV Designer deve-se realizar 4 tarefas:
- Cria��o dos componentes (widgets) que far�o parte da interface, como Bot�es e Textfields. Os componentes criados podem ser visualizados de duas maneiras, como mostrado na figura;

 \image html images/objects.png 

- Selecionar os layouts vertical e horizontal (Group Layout);

 \image html images/group.png 

- Adi��o de grupos Paralelos e sequenciais (ParallelGroupPanel e SequentialGroupPanel) aos Group Layouts;

 \image html images/panel.png 

- Adi��o dos componentes aos grupos. 

\image html images/adicao.png 


O SCV permite a defini��o de layouts nos eixos horizontal e vertical. Cabe a usu�rio definir quais layouts v�o ser usados. Esses dois eixos devem ser definidos caso se deseje que os componentes tenham comportamentos de redimensionamento nos dois eixos.

- Horizontal Group Layout: Define a propriedade de redimensionamento e distribui��o dos componentes no eixo horizontal. 
- Vertical Group Layout: Define a propriedade de redimensionamento e distribui��o dos componentes no eixo horizontal. 

Em cada Group Layout pode-se adicionar GroupsPanels, que podem ser sequenciais ou paralelos (ParallelGroupPanel e SequentialGroupPanel). Um grupo sequencial permite que componentes sejam adicionados um ao lado do outro (no Horizontal Group Layout) ou um abaixo no outro (no Vertical Group Layout). Grupos paralelos permitem criar linhas (no Horizontal Group Layout), ou colunas (no Vertical Group Layout) que dividem a tela, para facilitar a distribui��o de widgets. Pode-se fazer agrupamentos hier�rquicos destes componentes.  

\section Exemplos de Interfaces

- Exemplo 1: Apresenta uma interface que possui dois bot�es ( a) Vertical e Horizontal Group Layouts  b) Somente Horizontal Group Layout). Esses bot�es devem ser configurados para sempre ocuparem toda a �rea da janela, ou seja, todos os espa�os vertical e horizontal. Para isso, deve-se usar os Vertical e Horizontal Group Layouts. 

\image html images/exemplo1b.png 
\image html images/exemplo1a.png 
\image html images/exemplo1c.png

Como a interface possui apenas dois bot�es, dispostos um ao lado do outro, pode-se criar apenas tr�s GroupPanels: um sequencial no Horizontal Group Layout e dois paralelos no Vertical Group Layout.

O grupo sequencial faz com que um bot�o fique ao lado do outro (horizontalmente) e ocupe todo o espa�o em largura da tela, e o grupo paralelo faz o redimensionamento na vertical. Caso n�o seja especificado o layout Vertical, os bot�es n�o apresentam o redimensionamento vertical, e ficam com a altura m�nima definda.


 
- Exemplo 2: Apresenta uma interface com 4 bot�es, dispostos em linhas e colunas. 

\image html images/exemplo2a.png 
\image html images/exemplo2b.png 
\image html images/exemplo2c.png 

Para o Horizontal Group Layout, deve-se inicialmente definir um grupo paralelo que vai englobar dois grupos sequenciais, de modo a formar duas fileiras sequenciais e paralelas de bot�es. Para o Vertical Group Layout, deve-se ter um grupo paralelo que possui dois grupos sequencias. Caso n�o fosse usado o Vertical Group Layout, as duas fileiras de bot�es horizontais ficariam sobrepostas, sendo exibido apenas a segunda fileira. Al�m disso, por n�o haver redimensionamento vertical, os bot�es ocupariam a altura m�nima estipulada. 


- Exemplo 3: Este exemplo � semelhante ao caso anterior, por�m possui apenas 1 bot�o na esquerda e dois a direita. 

\image html images/exemplo3a.png 
\image html images/exemplo3b.png 
\image html images/exemplo3c.png 

Como o bot�o da esquerda deve ocupar todo o lado da janela, deve-se mudar a organiza��o dos Layouts. Para este exemplo foi criado um Grupo sequencial no Horizontal Group Layout, adicionado de dois grupos paralelos. O Layout Vertical � igual ao exemplo anterior. Para se obter o resultado da segunda figura, deve-se manter o mesmo layout, por�m o �Button 0� deve ser adicionado somente ao Horizontal Group Layout. Isso faz com que ele  n�o tenha redimensionamento no eixo Vertical. 


\section Gera��o de C�digo

O scv designer gera c�digo a partir da especifica��o. S�o gerados sempre 5 arquivos em linguagem C++. Esse c�digo pode ser visualizado na pr�pria interface do SCV Designer ou exportado para arquivos fonte (Menu Code):

\image html images/code.png 

- application.h: prot�tipos das callbacks e defini��o da classe application, 
- application.cpp: Defini��o e inicializa��o dos componentes, defini��o dos layouts
- main.cpp: inicializa��o do scv e execu��o. 
- widgets.h � prot�tipos das callbacks dos componentes. Deve-se habilitar a op��o �Generate Custom Class� para criar classes derivadas de cada widget.
- widgets.cpp� implementa��o das callbacks dos componentes.

\image html images/custonclass.png


*/

/*************************************************************************************
/*************************************************************************************
/*************************************************************************************
/*************************************************************************************
/*************************************************************************************

/*! \page freeform SCV Free Form Designer 

O SCV Free Form Designer � uma aplica��o opensource que foi desenvolvida sobre a API SCV para agilizar a constru��o de interfaces gr�ficas usando a API SCV. Ela deve proporcionar ao usu�rio a possibilidade de arranjar os componentes gr�ficos da API SCV de maneira visual, oferecendo recursos para adi��o ou remo��o de objetos, exporta��o do c�digo resultante e alinhamento autom�tico de componentes relacionados por diferentes esquemas de organiza��o. Ele tamb�m pode ser usado como ferramenta para estudo das funcionalidades e sintaxe de c�digo do SCV, ou como ferramenta para constru��o da base da aplica��o para posterior expans�o manual com demais componentes.

\section Interface

O SCV Free Form Designer apresenta uma estrutura simples, que possibilita a constru��o interativa da interface do software. Ela possui apenas uma janela com um painel, onde � poss�vel incluir componentes. A janela do SCV n�o possui um tamanho fixo, � poss�vel modificar o tamanho da janela arrastando suas bordas, para melhor se adequar a interface.

\image html images/freeform.png


\section Cria��o de Interfaces

Para criar uma interface no SCV Free Form Designer deve-se utilizar o menu, clicando com o bot�o direito na tela. O menu possui cinco op��es que est�o relacionados com a cria��o da interface: �Add Panel�, �Add Component�, �Clear Interface�, �Generate Code� e �Open�.

\image html images/menu.png

A op��o �Add Panel� � usado para adicionar pain�is na interface, os pain�is s�o utilizados para agrupar componentes (widgets). Existem cinco tipos de pain�is, como uma imagem ou um simples painel. 

\image html images/menu.png

Dentro de um painel � poss�vel adicionar outros pain�is ou componentes, os quais n�o ir�o aparecer fora do painel.

\image html images/remove.png

Ao mover o painel, todos os componentes que est�o em seu interior ir�o segui-lo. Clicando com o bot�o direito do mouse, pode-se remover componentes da interface. 



Ao clicar na op��o �Add Component� ir� aparecer um sub-menu com uma lista de todos os componentes.

\image html images/submenu.png

Ao clicar em algum componente ele ser� adicionado � tela na posi��o onde o mouse estava ao clicar com o bot�o direito, e estar� vinculado ao componente superior na hierarquia de componentes que j� foram adicionados � interface. Por exemplo, se o menu for aberto sobre um Panel, o novo componente ser� vinculado a este. Para mover um componente de posi��o, � preciso clicar no componente e arrasta-lo. � poss�vel modificar o tamanho de alguns componentes clicando em suas bordas e arrastando. Alguns componentes possuem uma Label, e ao adiciona-los aparecer� uma caixa de texto onde deve ser escrito aquilo que se deseja que apare�a no componente.

\image html images/caixa.png

A op��o �Clear Interface� ir� remover todos os componentes e pain�is da tela, restando apenas o painel inicial.

\section Gera��o de C�digo

O SCV Free Form designer gera c�digo a partir dos componentes inclu�dos na interface. Para gerar o c�digo � necess�rio clicar na op��o �Generate Code...�. S�o gerados sempre cinco arquivos em linguagem C++, que s�o os seguintes:
- application.h: prot�tipos das callbacks e defini��o da classe application.
- application.cpp: Defini��o e inicializa��o dos componentes.
- main.cpp: inicializa��o do scv e execu��o. 
- widgets.h � prot�tipos das callbacks dos componentes. 
- widgets.cpp� implementa��o das callbacks dos componentes.

Os arquivos s�o criados dentro da pasta Exported Source, presente dentro da pasta raiz do SCV.







*/
