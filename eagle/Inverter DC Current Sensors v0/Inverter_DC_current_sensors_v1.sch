<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.6.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="no" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="no" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="no" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="no" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="no" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="no" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="no" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="no" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="no" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="MHR15-TS">
<packages>
<package name="CSLA1DJ">
<wire x1="-17.8" y1="-7.1" x2="17.8" y2="-7.1" width="0.127" layer="21"/>
<wire x1="17.8" y1="-7.1" x2="17.8" y2="7.1" width="0.127" layer="21"/>
<wire x1="17.8" y1="7.1" x2="-17.8" y2="7.1" width="0.127" layer="21"/>
<wire x1="-17.8" y1="7.1" x2="-17.8" y2="-7.1" width="0.127" layer="21"/>
<hole x="-15.24" y="0" drill="2.921"/>
<hole x="15.24" y="0" drill="2.921"/>
<pad name="+12VDC" x="0" y="-2.54" drill="0.762" diameter="1.4224" shape="square"/>
<pad name="SIG_OUT" x="0" y="0" drill="0.762" diameter="1.4224"/>
<pad name="GND" x="0" y="2.54" drill="0.762" diameter="1.4224"/>
<text x="-2.54" y="-3.81" size="1.778" layer="27">3
2
1</text>
<text x="3.175" y="-3.81" size="1.778" layer="25" align="bottom-right">-
O
+</text>
<text x="22.86" y="-2.54" size="2.54" layer="25" rot="R90" align="bottom-right">I</text>
<polygon width="0.127" layer="25">
<vertex x="21.59" y="5.08"/>
<vertex x="19.05" y="2.54"/>
<vertex x="20.32" y="2.54"/>
<vertex x="20.32" y="-1.27"/>
<vertex x="22.86" y="-1.27"/>
<vertex x="22.86" y="2.54"/>
<vertex x="24.13" y="2.54"/>
</polygon>
<text x="-16.51" y="-8.89" size="1.778" layer="21">&gt;VALUE</text>
<text x="-16.51" y="8.255" size="2.54" layer="21">&gt;NAME</text>
<hole x="-10.16" y="0" drill="3.302"/>
<hole x="10.16" y="0" drill="3.302"/>
</package>
</packages>
<symbols>
<symbol name="CSLA1DJ">
<wire x1="0" y1="0" x2="15.24" y2="0" width="0.254" layer="94"/>
<wire x1="15.24" y1="0" x2="15.24" y2="-10.16" width="0.254" layer="94"/>
<wire x1="15.24" y1="-10.16" x2="0" y2="-10.16" width="0.254" layer="94"/>
<wire x1="0" y1="-10.16" x2="0" y2="0" width="0.254" layer="94"/>
<pin name="+12VDC" x="20.32" y="-2.54" length="middle" rot="R180"/>
<pin name="SIG_OUT" x="20.32" y="-5.08" length="middle" rot="R180"/>
<pin name="GND" x="20.32" y="-7.62" length="middle" rot="R180"/>
<text x="0" y="-12.7" size="1.778" layer="96">&gt;VALUE</text>
<text x="0" y="2.54" size="1.778" layer="95" align="top-left">&gt;NAME</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="CSLA1DJ">
<gates>
<gate name="G$1" symbol="CSLA1DJ" x="0" y="0"/>
</gates>
<devices>
<device name="" package="CSLA1DJ">
<connects>
<connect gate="G$1" pin="+12VDC" pad="+12VDC"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="SIG_OUT" pad="SIG_OUT"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="mhybrid molex megaFit">
<packages>
<package name="MOLEXMINIFIT6">
<wire x1="-5.8" y1="7.5" x2="5.8" y2="7.5" width="0.127" layer="21"/>
<wire x1="5.8" y1="7.5" x2="5.8" y2="-13.9" width="0.127" layer="21"/>
<wire x1="5.8" y1="-13.9" x2="-5.8" y2="-13.9" width="0.127" layer="21"/>
<wire x1="-5.8" y1="-13.9" x2="-5.8" y2="7.5" width="0.127" layer="21"/>
<pad name="CKT4" x="-2.1" y="5.5" drill="1.8"/>
<pad name="CKT3" x="2.1" y="5.5" drill="1.8"/>
<pad name="CKT2" x="-2.1" y="0" drill="1.8"/>
<pad name="CKT1" x="2.1" y="0" drill="1.8" shape="square"/>
<text x="-5.81" y="-15.65" size="1.27" layer="25">&gt;Name</text>
<hole x="0" y="-7.3" drill="3"/>
</package>
</packages>
<symbols>
<symbol name="MHYBRIDMOLEX">
<wire x1="2.54" y1="17.78" x2="10.16" y2="17.78" width="0.254" layer="94"/>
<wire x1="10.16" y1="17.78" x2="10.16" y2="5.08" width="0.254" layer="94"/>
<wire x1="10.16" y1="5.08" x2="2.54" y2="5.08" width="0.254" layer="94"/>
<wire x1="2.54" y1="5.08" x2="2.54" y2="17.78" width="0.254" layer="94"/>
<pin name="V_IN(12)" x="12.7" y="15.24" visible="pad" length="middle" rot="R180"/>
<pin name="V_IN2(12)" x="12.7" y="12.7" visible="pad" length="middle" rot="R180"/>
<pin name="GND" x="12.7" y="10.16" visible="pad" length="middle" rot="R180"/>
<pin name="GND2" x="12.7" y="7.62" visible="pad" length="middle" rot="R180"/>
<text x="2.54" y="20.32" size="2.54" layer="95">&gt;Name</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="MHYBRIDMOLEX" prefix="WTB">
<gates>
<gate name="G$1" symbol="MHYBRIDMOLEX" x="-5.08" y="-12.7"/>
</gates>
<devices>
<device name="" package="MOLEXMINIFIT6">
<connects>
<connect gate="G$1" pin="GND" pad="CKT1"/>
<connect gate="G$1" pin="GND2" pad="CKT2"/>
<connect gate="G$1" pin="V_IN(12)" pad="CKT3"/>
<connect gate="G$1" pin="V_IN2(12)" pad="CKT4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="SENS_INV" library="MHR15-TS" deviceset="CSLA1DJ" device=""/>
<part name="WTB1" library="mhybrid molex megaFit" deviceset="MHYBRIDMOLEX" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="SENS_INV" gate="G$1" x="33.02" y="68.58"/>
<instance part="WTB1" gate="G$1" x="88.9" y="73.66" rot="R180"/>
</instances>
<busses>
</busses>
<nets>
<net name="N$1" class="0">
<segment>
<pinref part="SENS_INV" gate="G$1" pin="+12VDC"/>
<pinref part="WTB1" gate="G$1" pin="GND2"/>
<wire x1="53.34" y1="66.04" x2="76.2" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="SENS_INV" gate="G$1" pin="GND"/>
<wire x1="53.34" y1="60.96" x2="66.04" y2="60.96" width="0.1524" layer="91"/>
<wire x1="66.04" y1="60.96" x2="66.04" y2="63.5" width="0.1524" layer="91"/>
<pinref part="WTB1" gate="G$1" pin="GND"/>
<wire x1="66.04" y1="63.5" x2="76.2" y2="63.5" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="SENS_INV" gate="G$1" pin="SIG_OUT"/>
<wire x1="53.34" y1="63.5" x2="60.96" y2="63.5" width="0.1524" layer="91"/>
<wire x1="60.96" y1="63.5" x2="60.96" y2="58.42" width="0.1524" layer="91"/>
<pinref part="WTB1" gate="G$1" pin="V_IN(12)"/>
<wire x1="60.96" y1="58.42" x2="76.2" y2="58.42" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="6.3" minversion="6.2.2" severity="warning">
Since Version 6.2.2 text objects can contain more than one line,
which will not be processed correctly with this version.
</note>
</compatibility>
</eagle>
