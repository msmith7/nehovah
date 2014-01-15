<!doctype html>
<html>
  <head>
    <link rel="stylesheet" type="text/css" href="index.css" />
    <meta charset="utf-8">
    <title>Nehovah</title>		
		<link type="text/css" href="jquery/css/overcast/jquery-ui-1.8.18.custom.css" rel="stylesheet" />	
		<script type="text/javascript" src="jquery/js/jquery-1.7.1.min.js"></script>
		<script type="text/javascript" src="jquery/js/jquery-ui-1.8.18.custom.min.js"></script>
<body bgcolor="#303030">
  </head>
  <body bgcolor="#303030">

    <script>
	$(function() {
		$( "#iv > span" ).each(function(index) {
			// read initial values from markup and remove that
			var value = parseInt( $( this ).text(), 10 );
			$( this ).empty().slider({
				value: value,
				range: "min",
				min: 0,
				max: 200,
				animate: true,
				orientation: "vertical",
				slide: function( event, ui) {
					$("#svalue"+index ).val(ui.value);
				}
			});
		});
		$( "#svalue0" ).val(100);
		$( "#svalue1" ).val(100);
		$( "#svalue2" ).val(100);
		$( "#svalue3" ).val(100);
	});

	$(document).ready(function()
	{
		$("#output").hide();
		$("#sbutton").click(function(event) 
			{
				$("#accordion").html(" ");
				$("#theform").hide();
				//alert("Nehovah is not ready to create words yet");
				//$(this).hide("slow");
				event.preventDefault();
				var words = new Array();
				words[0]  = $("#word0").val().toLowerCase();
				words[1]  = $("#word1").val().toLowerCase();
				if(words[0].length > 0 && words[1].length > 0)
				{
				words.sort();
				var wordFile = words[0] + '_' +words[1] + ".out";
				//alert(wordFile);
				var retrv = "http://axon.cs.byu.edu/~nehovah/retriever.php?"
						+ "word0=" + words[0]
						+ "&word1=" + words[1]
						+ "&s0=" + $("#svalue0").val()
						+ "&s1=" + $("#svalue1").val()
						+ "&s2=" + $("#svalue2").val()
						+ "&s3=" + $("#svalue3").val()
						+ "&fname=" + wordFile + "#";
				//alert(retrv);
				//clear output
				

				$.get(retrv, function(data) 
				{
					$("#output").show();
					var lines = data.split('\n');
					var count = 0;
					jQuery.each(lines, function()
					{
						if(this.length > 1)
						{
						var word = this.substring(0,this.indexOf(' '));
						var wordSpace1 = this.indexOf(' ');
						var wordSpace2 = this.indexOf(' ',wordSpace1+1);
						var wordSpace3 = this.indexOf(' ',wordSpace2+1);
						var wordSpace4 = this.indexOf(' ',wordSpace3+1);
						var wordSpace5 = this.indexOf(' ',wordSpace4+1);
						var scorePop = this.substring(wordSpace1+1,wordSpace2);
						var scoreCon = this.substring(wordSpace2+1,wordSpace3);
						var scoreSyl = this.substring(wordSpace3+1,wordSpace4);
						var scoreUni = this.substring(wordSpace4+1,wordSpace5);
						var score = ($("#svalue0").val()*1 + $("#svalue1").val()*1  + $("#svalue2").val()*1 + $("#svalue3").val()*1);
						var score = ((scorePop * $("#svalue0").val()) + (scoreCon * $("#svalue1").val()) + (scoreSyl * $("#svalue2").val()) + (scoreUni * $("#svalue3").val()))/($("#svalue0").val()*1 + $("#svalue1").val()*1 + $("#svalue2").val()*1 + $("#svalue3").val()*1);
						var bar1 = this.indexOf('|');
						var bar2 = this.indexOf('|', bar1+1);
						var bar3 = this.indexOf('|', bar2+1);
						var bar4 = this.indexOf('|', bar3+1);
						var bar5 = this.indexOf('|', bar4+1);
						var bar6 = this.indexOf('|', bar5+1);
						var root1_all = this.substring(bar1+1,bar2);
						var root2_all = this.substring(bar3+1,bar4);
						var endings   = this.substring(bar5+1,bar6);
						var space1 = root1_all.indexOf(' ');
						var root1_info = "<b>Prefix Root: </b>";
						//Prefix info
						if(space1 >= 0)
						{
							var root1_word = root1_all.substring(0,space1);
							var root1_pcr  = " <b>from</b> "+root1_all.substr(space1+1);
							root1_info = root1_info+root1_word+root1_pcr;
						} else
						{
							root1_info = root1_info + root1_all;
						}
						//Parse Endings
						var hasendings = false;
						var ending = [];

						if(endings.length > 0)
						{
							hasendings = true;
							var ending_temp = [];
							ending_temp = endings.split(' ');
							ending_temp.shift();
							jQuery.each(ending_temp, function()
							{
								if(this.length > 0)
								{
									ending.push(this.substring(1));
								}
								//$("#references").append(" |" + this.substring(1) + "|");
							});
							
						}
						//Suffix info
						var space2 = root2_all.indexOf(' ');
						var root2_info = "<br /><b>Suffix Root";
						if(hasendings)
						{
							root2_info += "s";
						} 
						root2_info += ": </b>";
						if(space2 >= 0)
						{
							var root2_word = root2_all.substring(0,space2);
							var root2_pcr  = " <b>from</b> "+root2_all.substr(space2+1);
							if(hasendings)
							{
								var word_temp = "";
								jQuery.each(ending, function()
								{
									word_temp = word_temp+root2_word + this + ", ";
								});
								root2_word = word_temp.substr(0,word_temp.length-2);
							}
							root2_info = root2_info+root2_word+root2_pcr;	
						} else
						{
							if(hasendings)
							{
								var word_temp = "";
								jQuery.each(ending, function()
								{
									word_temp = word_temp+root2_all + this + ", ";
								});
								root2_all = word_temp.substr(0,word_temp.length-2);
							}
							root2_info += root2_all;
						}
						var alternate_forms = "";
						if(hasendings)
						{
							alternate_forms = word;
							var word_temp = "";
							jQuery.each(ending, function()
							{
								word_temp = word_temp+ word + this + ", ";
							});
							alternate_forms = word_temp.substr(0,word_temp.length-2);
							word=word+ending[0];
							alternate_forms = "<b>Alternate Forms: </b>" + alternate_forms + "<br />";
						}
						$("#accordion").append("<h3><a href=\"#\">" + word +"\n</a></h3>Score: "+ score+"\n"
							+ "<div id=\"wordinfo\">"+alternate_forms+root1_info+root2_info+"<br><b>Pop Culture score:</b> "+scorePop+"<br><b>Concepts Score:</b> "+scoreCon+"<br><b>Syllables Score:</b> "+scoreSyl+"<br><b>Unique Score:</b> "+scoreUni+"</div>")
							.accordion('destroy').accordion({event: "mouseover", fillSpace: true});
						$("#output").show();
						}
					});
				});
				} else
				{
					alert("One or more of the words are blank!");
				}
				$("#theform").show();

			});
	});
	$("#accordion").change(function()
	{
		$( "#accordion" ).accordion(
		{
			event: "mouseover"
		});
	});
    </script>
<div id="vertcenter">
<div id="container" class="ui-widget ui-corner-all ui-helper-reset">
   <div id="title" class="ui-widget ui-corner-top">
       <b>NEHOVAH</b>
   </div>
   <div id="theform" class="ui-widget ui-corner-all">
	   <form>
	    <div id="wordinput" class="ui-widget">
		    Word 1: <input type="text" id="word0" name="word0" class="ui-corner-all" /> <br /> 
		    Word 2: <input type="text" id="word1" name="word1" class="ui-corner-all" /> <br /> 
           </div>
	    <div id="lbls" class="ui-widget">
		<span style="margin:0px;"><b>Pop culture  </b></span>
		<span style="margin:8px;"><b>Concepts  </b></span>
		<span style="margin:8px;"><b>Syllables  </b></span>
		<span style="margin:8px;"><b>Unique </b></span>
	    </div>
	    <div id="iv">
		<span>100</span>
		<span>100</span>
		<span>100</span>
		<span>100</span>
	    </div>
	    <input type="hidden" id="svalue0" name="slider0" /> 
	    <input type="hidden" id="svalue1" name="slider1" />
	    <input type="hidden" id="svalue2" name="slider2" />
	    <input type="hidden" id="svalue3" name="slider3" /><br /><br />
           <div id="sbutton" class="ui-widget">
		    <input type="submit" value="Submit" />
	    </div>
	   </form>
   </div>
   <div id="output" class="ui-corner-all">
	<div id="outcontainer">
		<div id="accordion">
		</div>
	</div>
   </div>
   <br />
   <br />
   <div id="references">
    <a href="http://byu.edu">BYU</a> - 
    <a href="http://cs.byu.edu">Computer Science</a> -
    <a href="http://axon.cs.byu.edu">Machine Learning and Neural Networks Lab</a> -
<!--    <a href="mailto:nehovah@axon.cs.byu.edu">Suggestions</a> -->
    <a href="mailto:mrsmith@byu.edu">Suggestions</a> 
<br>
    Created by: <a href="http://axon.cs.byu.edu/~msmith">Michael R. Smith</a> and Ryan S. Hintze
   </div>
</div>
</div>
  </body>
</html>
