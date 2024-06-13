"""
Author: Gabriel Morberg
Email: gabrielmorberg13@gmail.com / c21gmg@cs.umu.se
Since: 2024-06-13
Version: 1.0
Description: This script takes a markdown file as input and converts it to a XML file that is compatible with 
             the IMS QTI standard. Thereafter the zip file can be used to import a quizbank in the Canvas LMS.
             For format of the markdown file see the README.md file.
Usage : python3 qparser.py <markdown_file.md>
Limitations : The script only supports multiple choice and multiple answers questions.
              The questions can only be formatted in text and code blocks.
"""

import markdown
import xml.etree.ElementTree as ET
from xml.dom import minidom
import re
import uuid
import sys
import zipfile

def zip_xml_file(xml_content,zip_filename):

    zip_filename = zip_filename + ".zip"
    with zipfile.ZipFile(zip_filename, 'w') as zipf:
        zipf.writestr("output.xml", xml_content)

def find_bank_title(markdown_file):
    with open(markdown_file, 'r', encoding='utf-8') as f:
        for line in f:
            if line.startswith('#'):
                bank_title = line.replace('#', '')  
                bank_title = bank_title.strip()
                break
        else:
            bank_title = "Untitled Bank"
            print("No title found in markdown file, using default title")
    return bank_title

def parse_markdown_to_xml(markdown_file):
    with open(markdown_file, 'r', encoding='utf-8') as f:
        markdown_content = f.read()

    html_content = markdown.markdown(markdown_content)

    root = ET.Element('questestinterop')
    root.set('xmlns', 'http://www.imsglobal.org/xsd/ims_qtiasiv1p2')
    root.set('xmlns:xsi', 'http://www.w3.org/2001/XMLSchema-instance')
    root.set('xsi:schemaLocation', 'http://www.imsglobal.org/xsd/ims_qtiasiv1p2 http://www.imsglobal.org/xsd/ims_qtiasiv1p2p1.xsd')

    objectbank_ident = str(uuid.uuid4())
    objectbank = ET.SubElement(root, 'objectbank', ident=objectbank_ident)

    bank_title = find_bank_title(markdown_file)
    qtimetadata = ET.SubElement(objectbank, 'qtimetadata')
    qtimetadatafield1 = ET.SubElement(qtimetadata, 'qtimetadatafield')
    fieldlabel1 = ET.SubElement(qtimetadatafield1, 'fieldlabel')
    fieldlabel1.text = 'bank_title'
    fieldentry1 = ET.SubElement(qtimetadatafield1, 'fieldentry')
    fieldentry1.text = bank_title

    questions = re.findall(r'<h2>(.*?)<\/h2>(.*?)<\/ul>', html_content, re.DOTALL)
    # Question title is the name after the colon in the bank title
    questions_title = bank_title.split(":")[1].strip()
    
    if not questions_title:
        #Handle case where there is no colon in the bank title
        questions_title = "Fråga"

    for index, (title, question_content) in enumerate(questions):
        #Create unique identifier for each question
        ident = str(uuid.uuid4())

        # Hardcode the title
        item = ET.SubElement(objectbank, 'item', ident=ident, title=questions_title)
        itemmetadata = ET.SubElement(item, 'itemmetadata')
        qtimetadata = ET.SubElement(itemmetadata, 'qtimetadata')

        qtimetadatafield1 = ET.SubElement(qtimetadata, 'qtimetadatafield')
        fieldlabel1 = ET.SubElement(qtimetadatafield1, 'fieldlabel')
        fieldlabel1.text = 'question_type'
        fieldentry1 = ET.SubElement(qtimetadatafield1, 'fieldentry')

        qtimetadatafield2 = ET.SubElement(qtimetadata, 'qtimetadatafield')
        fieldlabel2 = ET.SubElement(qtimetadatafield2, 'fieldlabel')
        fieldlabel2.text = 'points_possible'
        fieldentry2 = ET.SubElement(qtimetadatafield2, 'fieldentry')
        fieldentry2.text = '1.0'

        presentation = ET.SubElement(item, 'presentation')
        material = ET.SubElement(presentation, 'material')
        mattext = ET.SubElement(material, 'mattext', texttype="text/html")
     
        paragraphs = re.findall(r'<p>(.*?)</p>', question_content, re.DOTALL)
        cleaned_question = '\n'.join(paragraphs)
        cleaned_question = re.sub(r'<code>(.*?)</code>', r'<pre><code>\1</code></pre>', cleaned_question,flags=re.DOTALL)
        
        mattext.text = cleaned_question

        response_lid = ET.SubElement(presentation, 'response_lid', ident="response1")
        render_choice = ET.SubElement(response_lid, 'render_choice')

        answers = re.findall(r'<li>\[(x| )\] (.*?)<\/li>', question_content)
        correct_count = sum(1 for is_correct, _ in answers if is_correct.strip() == 'x')

        rcardinality = "Single" if correct_count == 1 else "Multiple"
        response_lid.set('rcardinality', rcardinality)

        original_answer_ids = []
        correct_answers = []
        for index, (is_correct, answer_text) in enumerate(answers):
            response_ident = str(uuid.uuid4())
            original_answer_ids.append(response_ident)
            if is_correct.strip() == 'x':
                correct_answers.append(response_ident)

            response_label = ET.SubElement(render_choice, 'response_label', ident=response_ident)
            material = ET.SubElement(response_label, 'material')
            mattext = ET.SubElement(material, 'mattext', texttype="text/plain")
            mattext.text = answer_text.strip()

        qtimetadatafield3 = ET.SubElement(qtimetadata, 'qtimetadatafield')
        fieldlabel3 = ET.SubElement(qtimetadatafield3, 'fieldlabel')
        fieldlabel3.text = 'original_answer_ids'
        fieldentry3 = ET.SubElement(qtimetadatafield3, 'fieldentry')
        fieldentry3.text = ','.join(original_answer_ids)

        resprocessing = ET.SubElement(item, 'resprocessing')
        outcomes = ET.SubElement(resprocessing, 'outcomes')
        decvar = ET.SubElement(outcomes, 'decvar', maxvalue="100", minvalue="0", varname="SCORE", vartype="Decimal")

        respcondition = ET.SubElement(resprocessing, 'respcondition')
        respcondition.set('continue', "No")
        conditionvar = ET.SubElement(respcondition, 'conditionvar')
        
        if correct_count == 1:
            fieldentry1.text = 'multiple_choice_question'
            varequal = ET.SubElement(conditionvar, 'varequal', respident="response1")
            varequal.text = correct_answers[0]
        else:
            fieldentry1.text = 'multiple_answers_question'
            condition_and = ET.SubElement(conditionvar, 'and')
            for correct_answer in correct_answers:
                varequal = ET.SubElement(condition_and, 'varequal', respident="response1")
                varequal.text = correct_answer
            for incorrect_answer in set(original_answer_ids) - set(correct_answers):
                not_condition = ET.SubElement(condition_and, 'not')
                varequal = ET.SubElement(not_condition, 'varequal', respident="response1")
                varequal.text = incorrect_answer

        setvar = ET.SubElement(respcondition, 'setvar', action="Set", varname="SCORE")
        setvar.text = "100"

    xml_str = ET.tostring(root, encoding='unicode', xml_declaration=True)
    xml_dom = minidom.parseString(xml_str)
    pretty_xml_str = xml_dom.toprettyxml(indent="  ")
    return pretty_xml_str





if len(sys.argv) != 2:
    print("Usage: python3 qparser.py <markdown_file.md>")
    sys.exit(1)

md_file = sys.argv[1]
xml_content = parse_markdown_to_xml(md_file)

mdfile_name = md_file.split(".")[0]

zip_xml_file(xml_content,mdfile_name)
