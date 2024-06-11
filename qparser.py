import markdown
import xml.etree.ElementTree as ET
from xml.dom import minidom
import re
import uuid

"""
"Zip XML file, takes an XML file as input and zips it into a file with the same name but with the extension .zip"
"Input: xml_file: str, the name of the XML file to be zipped"
"Output: Zip file with the same name as the input XML file but with the extension .zip"
"Example: zip_xml_file('quiz.xml') -> 'quiz.zip'"
"""
def zip_xml_file(xml_file):
    import zipfile
    import os

    # Create a Zip file
    with zipfile.ZipFile(xml_file.replace('.xml', '.zip'), 'w') as zipf:
        zipf.write(xml_file)


def parse_markdown_to_xml(markdown_file):
    # Read Markdown file
    with open(markdown_file, 'r', encoding='utf-8') as f:
        markdown_content = f.read()

    # Convert Markdown to HTML
    html_content = markdown.markdown(markdown_content)

    # Create XML tree
    root = ET.Element('questestinterop')
    root.set('xmlns', 'http://www.imsglobal.org/xsd/ims_qtiasiv1p2')
    root.set('xmlns:xsi', 'http://www.w3.org/2001/XMLSchema-instance')
    root.set('xsi:schemaLocation', 'http://www.imsglobal.org/xsd/ims_qtiasiv1p2 http://www.imsglobal.org/xsd/ims_qtiasiv1p2p1.xsd')

    # Read bank title from the first line of the Markdown file
    with open(markdown_file, 'r', encoding='utf-8') as f:
        bank_title = f.readline().strip()
        

    # Create objectbank-tag with identifier and title
    objectbank_ident = str(uuid.uuid4())
    objectbank = ET.SubElement(root, 'objectbank', ident=objectbank_ident)

    # Add bank title
    qtimetadata = ET.SubElement(objectbank, 'qtimetadata')
    qtimetadatafield1 = ET.SubElement(qtimetadata, 'qtimetadatafield')
    fieldlabel1 = ET.SubElement(qtimetadatafield1, 'fieldlabel')
    fieldlabel1.text = 'bank_title'
    fieldentry1 = ET.SubElement(qtimetadatafield1, 'fieldentry')
    fieldentry1.text = bank_title

    # Loop through each question in HTML content
    questions = re.findall(r'<h2>(.*?)<\/h2>(.*?)<\/ul>', html_content, re.DOTALL)
    for title, question_content in questions:
        # Generate a unique identifier for the question
        ident = str(uuid.uuid4())
       
        item = ET.SubElement(objectbank, 'item', ident=ident, title=title.strip())
        itemmetadata = ET.SubElement(item, 'itemmetadata')
        qtimetadata = ET.SubElement(itemmetadata, 'qtimetadata')
        
        # Create question_type
        qtimetadatafield1 = ET.SubElement(qtimetadata, 'qtimetadatafield')
        fieldlabel1 = ET.SubElement(qtimetadatafield1, 'fieldlabel')
        fieldlabel1.text = 'question_type'
        fieldentry1 = ET.SubElement(qtimetadatafield1, 'fieldentry')
        fieldentry1.text = 'multiple_choice_question'

        # Create points_possible
        qtimetadatafield2 = ET.SubElement(qtimetadata, 'qtimetadatafield')
        fieldlabel2 = ET.SubElement(qtimetadatafield2, 'fieldlabel')
        fieldlabel2.text = 'points_possible'
        fieldentry2 = ET.SubElement(qtimetadatafield2, 'fieldentry')
        fieldentry2.text = '1.0'

        presentation = ET.SubElement(item, 'presentation')
        material = ET.SubElement(presentation, 'material')
        mattext = ET.SubElement(material, 'mattext', texttype="text/html")
        
        # Construct the cleaned question
        paragraphs = re.findall(r'<p>(.*?)</p>', question_content, re.DOTALL)
        cleaned_question = '\n'.join(paragraphs)
        
        # Add <pre> tag around <code> tag
        cleaned_question = re.sub(r'<code>(.*?)</code>', r'<pre><code>\1</code></pre>', cleaned_question)

        mattext.text = cleaned_question

        response_lid = ET.SubElement(presentation, 'response_lid', ident="svar1", rcardinality="Single")
        render_choice = ET.SubElement(response_lid, 'render_choice')

        # Create response options
        answers = re.findall(r'<li>\[(x| )\] (.*?)<\/li>', question_content)
        correct_index = 1
        incorrect_index = 1
        for is_correct, answer_text in answers:
            # Determine identifier based on correctness
            if is_correct.strip() == 'x':
                ident = "korrekt" + str(correct_index)
                correct_index += 1
            else:
                ident = "fel" + str(incorrect_index)
                incorrect_index += 1

            # Create response label
            response_label = ET.SubElement(render_choice, 'response_label', ident=ident)
            material = ET.SubElement(response_label, 'material')
            mattext = ET.SubElement(material, 'mattext', texttype="text/plain")
            mattext.text = answer_text.strip()

        resprocessing = ET.SubElement(item, 'resprocessing')
        outcomes = ET.SubElement(resprocessing, 'outcomes')
        decvar = ET.SubElement(outcomes, 'decvar', maxvalue="100", minvalue="0", varname="SCORE", vartype="Decimal")
        
        respcondition = ET.SubElement(resprocessing, 'respcondition')
        conditionvar = ET.SubElement(respcondition, 'conditionvar')

        # Search for correct response labels
        for i in range(1, correct_index):
            varequal = ET.SubElement(conditionvar, 'varequal', respident="svar1")
            varequal.text = "korrekt" + str(i)
            setvar = ET.SubElement(respcondition, 'setvar', action="Set", varname="SCORE")
            setvar.text = '100'

    # Convert XML to string and format with minidom
    xml_str = ET.tostring(root, encoding='unicode', xml_declaration=True)
    xml_dom = minidom.parseString(xml_str)
    pretty_xml_str = xml_dom.toprettyxml(indent="  ")

    # Write XML to file
    with open('quiz.xml', 'w', encoding='utf-8') as f:
        f.write(pretty_xml_str)

# Usage example
parse_markdown_to_xml("quizbank_variabler.md")