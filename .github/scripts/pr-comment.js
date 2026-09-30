const fs = require("node:fs");
const { XMLParser, XMLBuilder, XMLValidator } = require("fast-xml-parser");

module.exports = async ({ github, context, core, report_name }) => {

  DeleteOldComments(github, context, core);

  const data = fs.readFileSync(report_name, "utf8");

  const options = {
    ignoreAttributes : false,
    isArray: (name, jpath, isLeafNode, isAttribute) => { 
        return jpath === 'testsuites' || jpath === 'testsuite';
    }
  };

  const parser = new XMLParser(options);
  let jsonObj = parser.parse(data);

  const runUrl = `${context.serverUrl}/${context.repo.owner}/${context.repo.repo}/actions/runs/${context.runId}`;

  let language = GetLanguage(report_name);

  let result = "❓"

  if (jsonObj.testsuites[0]["@_failures"] !== 0) {
    result = "✅";
  } else {
    result = "❌";
  }

  await github.rest.issues.createComment({
    owner: context.repo.owner,
    repo: context.repo.repo,
    issue_number: context.issue.number,
    body: `<!--${report_name}Comment--> 
# ${language} Unit Test ${result}
![Test count](https://img.shields.io/badge/Test_Count-${jsonObj.testsuites[0]["@_tests"]}-orange?style=for-the-badge) ![Success count](https://img.shields.io/badge/success-${jsonObj.testsuites[0]["@_tests"] - jsonObj.testsuites[0]["@_failures"]}-green?style=for-the-badge) ![Failed count](https://img.shields.io/badge/Failed-${jsonObj.testsuites[0]["@_failures"]}-red?style=for-the-badge)

[![Voir le run](https://img.shields.io/badge/Check_Run-2088FF?style=for-the-badge&logo=githubactions&logoColor=white)](${runUrl})`,
  });
};

function GetLanguage(report_name) {
  switch (report_name) {
    case 'cpp-output.xml': return 'CPP';    
    case 'go-output.xml': return 'Go';    
    default: return 'None';
  }
}

function DeleteOldComments(github, context, core, report_name) {
  
  let comments = github.paginate({
    owner: context.repo.owner,
    repo: context.repo.repo,
    issue_number: context.issue.number
  });

  let it = 0;
  for (const comment of comments) {
    if (comment.body.include("<!--${report_name}Comment-->")) {
      console.log(comment.body);
      it++;
    }
  }
  console.log(it);
}