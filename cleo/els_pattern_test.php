<?php

//■

	$patternlength = 24;
	$patterns = 0;
	
	function dumppattern($pattern, $back = false){
		global $patternlength;
		if($back) $back = "7@";
		else $back = "6@";
		$last = "--";
		for($i = 0; $i < $patternlength; $i++){
			$p = $pattern[$i];
			if($p == " ") $p = "-";
			if($i == 0){
				echo("0006: 33@ = 0<br/>");
			} else {
				echo("000A: 33@ += 1<br/>");
			}
			$n = 0;
			if($last != $p){
				if($p == "-") $n = 1;
				if($p == "l") $n = 2;
				if($p == "r") $n = 3;
				if($p == "b") $n = 4;
			}
			echo("$back(33@,24i) = $n<br/>");
			$last = $p;
		}
		echo("jump @OWNELM_START");
	}

?>

<!DOCTYPE html>
<html lang="en">
<head>
	<title>els</title>
	<style type="text/css">
		a, a:hover, a:link, a:visited, a:active {
			color: #000055;
			text-decoration: none;
			display: block;
			width: 20px;
			height: 20px;
		}
		
		kbd {
			font-size: 14px;
		}
	</style>
</head>

<body onload="loop();">
	
	<div class="content">
		<kbd>
		<p>front</p>
		<table>
			<tr>
				<?php
					function addpattern($name, $pattern, $enabled = true){
						global $patterns, $patternlength;
						if($enabled) $enabled = 'checked="checked"';
						else $enabled = "";
						echo("<tr><td width=\"200\">".'<input type="checkbox" id="c'.$patterns.'" '.$enabled.'/>'."$name</td>");
						$c = 0;
						for($i = 0; $i < $patternlength; $i++){
							$p = $pattern[$i];
							if($p == " ") $p = "-";
							echo('<td><a id="p'."{$patterns}_$c".'" href="#" onclick="c(this);">'.strtoupper($p).'</a></td>');
							$c++;
						}
						echo('<td width="15" style="text-align: right" id="pattern_'.$patterns.'_L">&nbsp;</td>');
						echo('<td width="15" style="text-align: right">&nbsp;</td>');
						echo('<td width="15" style="text-align: right" id="pattern_'.$patterns.'_R">&nbsp;</td></tr>');
						$patterns++;
					}
					addpattern("strobe A", 				"l l   r r   l l   r r   ", false);
					addpattern("strobe B", 				"b b   b b   b b   b b   ", false);
					addpattern("hazard > slow", 		"llllllllllllrrrrrrrrrrrr", false);
					addpattern("hazard > normal", 		"llllllrrrrrrllllllrrrrrr", false);
					addpattern("hazard > fast", 		"lllrrrlllrrrlllrrrlllrrr", false);
					addpattern("hazard > faster", 		"llrrllrrllrrllrrllrrllrr", false);
					addpattern("full > slow", 			"      bbbbbbbbbbbb      ", false);
					addpattern("full > normal", 		"bbb      bbbbbb      bbb", false);
					addpattern("full > fast", 			"bbb   bbb   bbb   bbb   ", false);
					addpattern("full > faster", 		"bb  bb  bb  bb  bb  bb  ", false);
				?>
			</tr>
			
		</table>
		<p>rear</p>
		<table>
			<tr>
				<?php
					addpattern("strobe A", 				"b b   b b   b b   b b   ", false);
					addpattern("strobe B", 				"bbb   bbb   bbb   bbb   ", false);
					addpattern("strobe C", 				"   b b   b b   b b   b b", false);
					addpattern("strobe D", 				"   bbb   bbb   bbb   bbb", false);
					addpattern("full > slow", 			"      bbbbbbbbbbbb      ", false);
					addpattern("full > normal", 		"bbb      bbbbbb      bbb", false);
					addpattern("full > fast", 			"bbb   bbb   bbb   bbb   ", false);
					addpattern("full > faster", 		"bb  bb  bb  bb  bb  bb  ", false);
				?>
			</tr>
			
		</table>
		
		<?php
			
		
		?>
		</kbd>
		
	</div>
	
	<script type="text/javascript">
		var delay = 75;
		var patterns = <?php echo($patterns); ?>;
		var patternlength = <?php echo($patternlength); ?>;
		var index = 0;
		
		function loop(){
			for(var i = 0; i < patterns; i++){
				var l = document.getElementById('pattern_'+i+'_L');
				var r = document.getElementById('pattern_'+i+'_R');
				if(document.getElementById('c'+i).checked){
					var p = document.getElementById('p'+i+'_'+index).innerHTML;
					if(p == "L"){
						l.innerHTML = "\u25A0";
						r.innerHTML = " ";
					} else if(p == "R"){
						l.innerHTML = " ";
						r.innerHTML = "\u25A0";
					} else if(p == "B"){
						l.innerHTML = "\u25A0";
						r.innerHTML = "\u25A0";
					} else {
						l.innerHTML = " ";
						r.innerHTML = " ";
					}
				} else {
					l.innerHTML = " ";
					r.innerHTML = " ";
				}
			}
			index++;
			if(index >= patternlength) index = 0;
			id=setTimeout("loop()", delay);
		}
		
		
		function c(a){
			val = a.innerHTML;
			if(val == "L") a.innerHTML = "R";
			else if(val == "R") a.innerHTML = "B";	
			else if(val == "B") a.innerHTML = "-";	
			else if(val == "-") a.innerHTML = "L";		
		}
	</script>
	
</body>
</html>