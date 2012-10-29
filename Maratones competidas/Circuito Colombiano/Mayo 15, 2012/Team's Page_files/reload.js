/*/////////////////////////////////////////////////////////////////////////////////////////
//BOCA Online Contest Administrator. Copyright (c) 2003-2004 Cassio Polpo de Campos.
//It may be distributed under the terms of the Q Public License version 1.0. A copy of the
//license can be found with this software or at http://www.opensource.org/licenses/qtpl.php
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
//PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER
//OR HOLDERS INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT OR
//CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
//PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING
//OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
///////////////////////////////////////////////////////////////////////////////////////////
*/
var msg = 0;
var rld  = 0;
var selecionando = 0;
var seg = 120;
function recarregar() {
	if (rld) {
		clearTimeout(rld);
        	rld  = 0;
        }
        if ((document.form1 && document.form1.message && document.form1.message.value) ||
            (document.form1 && document.form1.sourcefile && document.form1.sourcefile.value) ||
            (document.form1 && document.form1.answer && document.form1.answer.value) ||
            (document.form2 && document.form2.answer && document.form2.answer.value) ||
            (document.form2 && document.form2.message && document.form2.message.value) ||
            (document.form2 && document.form2.sourcefile && document.form2.sourcefile.value) ||
            selecionando == 1) {
                if (msg<5) {
			msg++;
		}
		else {
alert("This page tried to reload, but it seems that you are filling\nthe form. To update, click on Reload button in your\nbrowser. This message will not be displayed again.");
                }
        } else
                document.location.reload();
        rld = setTimeout("recarregar()", seg * 1000);
}
function Comecar() {
	rld = setTimeout("recarregar()", seg * 1000);
}
function Parar() {
	if (rld) {
		clearTimeout(rld);
		rld  = 0;
	}
}
function Arquivo() {
	selecionando = 1;
}
